#include <bits/stdc++.h>
using namespace std;

const int rs = 5;
const int maxn = 705;
const int mod = 998244353;

int add(int x, int y) {
	return (x + y) % mod;
}

int mul(int x, int y) {
	return (1LL * x * y) % mod;
}

int fast_power(int x, int y) {
	if (y == 0) return 1;
	int h = fast_power(x, y / 2);
	int hh = mul(h, h);
	if (y % 2 == 0) return hh;
	return mul(hh, x);
}

int n;
int mt[rs][maxn][maxn];

// SIMD friendly?

void mt_addR(int x, int y, int z, int cx, int cy, int cz) {
	for (int i = 0; i < n; ++i) {
		mt[z][cz][i] = add(mt[x][cx][i], mt[y][cy][i]);
	}
}

void mt_add(int x, int y, int z) {
	for (int i = 0; i < n; ++i) {
		mt_addR(x, y, z, i, i, i);
	}
}

void mt_mulRI(int x, int k, int z, int cx, int cz) {
	for (int i = 0; i < n; ++i) {
		mt[z][cz][i] = mul(mt[x][cx][i], k);
	}
}

void mt_printR(int x, int cx) {
	for (int i = 0; i < n; ++i) {
		fprintf(stderr, "%d%c", mt[x][cx][i], " \n"[i == n - 1]);
	}
}

void mt_print(int x) {
	for (int i = 0; i < n; ++i) mt_printR(x, i);
}

void clear_x(int r, int b, int cx, int x, const vector<int> &y) {
	const int tv = 301;
	if (mt[r][cx][x] != 1) { 
		int inv = fast_power(mt[r][cx][x], mod - 2);
		mt_mulRI(r, inv, r, cx, cx);
		mt[2][b][cx] = mul(mt[2][b][cx], inv);
	}

	for (int cy : y) {
		if (cy == cx) continue;
		int k = mt[r][cy][x];
		if (k == 0) continue;
		mt_mulRI(r, mod - k, 2, cx, tv);
		mt_addR(r, 2, r, cy, tv, cy);
		mt[2][b][cy] = add(mt[2][b][cy], mod - mul(k, mt[2][b][cx]));
	}
}

int main() {
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	int Q;
	scanf("%d %d", &n, &Q);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) scanf("%d", mt[1][i] + j);
		scanf("%d", mt[2][0] + i);
	}

	vector<int> _all;
	for (int i = 0; i < n; ++i) _all.push_back(i);

	const int chunk = 27;
	for (int _ = 0; _ <= Q; _ += chunk) {
		const int sv = 100;
		vector<int> rows, rb;
		mt_addR(0, 0, 2, 0, 0, 7);

		for (int i = 0; i < chunk && i + _ <= Q; ++i) {
			if (i + _ == 0) {
				rows.push_back(0);
				mt_addR(1, 0, 2, 0, 0, sv + i);
				rb.push_back(mt[2][0][0]);
				continue;
			}

			int r;
			scanf("%d", &r);
			rows.push_back(r - 1);
			mt[2][7][r - 1] = 1;

			for (int j = 0; j < n; ++j) scanf("%d", mt[2][sv + i] + j);
			scanf("%d", &r);
			rb.push_back(r);
		}

		vector<int> Ac;
		for (int i = 0; i < n; ++i) {
			if (!mt[2][7][i]) Ac.push_back(i);
		}

		mt_add(1, 0, 3);
		mt_addR(2, 0, 2, 0, 0, 1);

		mt_addR(0, 0, 2, 0, 0, 9);
		mt_addR(0, 0, 2, 0, 0, 10);
		for (int x = 0; x < n; ++x) {
			int cx = -1;
			for (int i = 0; i < n; ++i) {
				if (mt[2][7][i] || mt[2][9][i]) continue;
				if (mt[3][i][x]) {
					cx = i;
					break;
				}
			}

			if (cx == -1) continue;
			mt[2][9][cx] = 1;
			mt[2][10][x] = cx + 1;
			clear_x(3, 1, cx, x, Ac);
		}

		for (int i = 0; i < rows.size(); ++i) {
			mt_add(3, 0, 4);
			mt_addR(2, 0, 2, 1, 0, 2);

//			mt_add(1, 0, 4);
//			mt_addR(2, 0, 2, 0, 0, 2);

			for (int j = i + 1; j < rows.size(); ++j) {
				int r = rows[j];
				mt_addR(1, 0, 4, r, 0, r);
				mt[2][2][r] = mt[2][0][r];
			}

			for (int j = 0; j <= i; ++j) {
				mt_addR(2, 0, 4, sv + j, 0, rows[j]);
				mt[2][2][rows[j]] = rb[j];
			}

//			mt_print(4);
//			mt_printR(2, 2);
//			fprintf(stderr, "===\n");

			mt_addR(2, 0, 2, 9, 0, 8);
			for (int x = 0; x < n; ++x) {
				if (mt[2][10][x]) {
					clear_x(4, 2, mt[2][10][x] - 1, x, rows);
					continue;
				}

				int cx = -1;
				for (int i = 0; i < n; ++i) {
					if (mt[4][i][x] && !mt[2][8][i]) {
						cx = i;
						break;
					}
				}

				if (cx == -1) continue;
				mt[2][8][cx] = 1;
				clear_x(4, 2, cx, x, _all);
			}

			for (int cx = 0; cx < n; ++cx) {
				for (int x = 0; x < n; ++x) {
					if (mt[4][cx][x]) goto NL;
				}
				if (mt[2][2][cx]) goto NS;
NL:				continue;
			}

			for (int x = 0; x < n; ++x) {
				int cx = -1;
				for (int i = 0; i < n; ++i) {
					if (mt[4][i][x]) {
						cx = i;
						break;
					}
				}

				if (cx == -1) goto NM;
				for (int i = 0; i < n; ++i) {
					if (i != x && mt[4][cx][i]) goto NM;
				}
				mt[2][3][x] = mt[2][2][cx];
			}

			for (int i = 0; i < n; ++i) {
				printf("%d%c", mt[2][3][i], " \n"[i == n - 1]);
			}
			continue;

NM:			puts("Many");
			continue;

NS:			puts("No");
//			mt_print(4);
//			mt_printR(2, 2);
//			fprintf(stderr, "\n\n");
		}

		for (int i = 0; i < rows.size(); ++i) {
			mt_addR(2, 0, 1, sv + i, 0, rows[i]);
			mt[2][0][rows[i]] = rb[i];
		}
	}
	return 0;
}
