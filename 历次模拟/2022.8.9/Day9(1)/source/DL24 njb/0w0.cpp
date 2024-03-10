#include <cstdio>

using namespace std;

const int N = 5e4 + 5;
const long long MOD = 4294967296;

struct Tree {
	long long val[16];
	char lz;
} t[N << 2];

char s[N];
int n, m;

inline void pushup(int p) {
	for (int i = 1; i <= 14; ++i) t[p].val[i] = (t[p << 1].val[i] + t[p << 1 | 1].val[i]) % MOD;
	t[p].val[2] = (t[p].val[2] + t[p << 1].val[10] * t[p << 1 | 1].val[4]) % MOD;
	t[p].val[2] = (t[p].val[2] + t[p << 1].val[12] * t[p << 1 | 1].val[6]) % MOD;
	t[p].val[2] = (t[p].val[2] + t[p << 1].val[14] * t[p << 1 | 1].val[8]) % MOD;
	t[p].val[3] = (t[p].val[3] + t[p << 1].val[1] * t[p << 1 | 1].val[10]) % MOD;
	t[p].val[4] = (t[p].val[4] + t[p << 1].val[11] * t[p << 1 | 1].val[6]) % MOD;
	t[p].val[4] = (t[p].val[4] + t[p << 1].val[13] * t[p << 1 | 1].val[8]) % MOD;
	t[p].val[5] = (t[p].val[5] + t[p << 1].val[1] * t[p << 1 | 1].val[12]) % MOD;
	t[p].val[5] = (t[p].val[5] + t[p << 1].val[3] * t[p << 1 | 1].val[11]) % MOD;
	t[p].val[6] = (t[p].val[6] + t[p << 1].val[10] * t[p << 1 | 1].val[8]) % MOD;
	t[p].val[7] = (t[p].val[7] + t[p << 1].val[1] * t[p << 1 | 1].val[14]) % MOD;
	t[p].val[7] = (t[p].val[7] + t[p << 1].val[3] * t[p << 1 | 1].val[13]) % MOD;
	t[p].val[7] = (t[p].val[7] + t[p << 1].val[5] * t[p << 1 | 1].val[10]) % MOD;
	t[p].val[9] = (t[p].val[9] + t[p << 1].val[1] * t[p << 1 | 1].val[2]) % MOD;
	t[p].val[9] = (t[p].val[9] + t[p << 1].val[3] * t[p << 1 | 1].val[4]) % MOD;
	t[p].val[9] = (t[p].val[9] + t[p << 1].val[5] * t[p << 1 | 1].val[6]) % MOD;
	t[p].val[9] = (t[p].val[9] + t[p << 1].val[7] * t[p << 1 | 1].val[8]) % MOD;
	t[p].val[12] = (t[p].val[12] + t[p << 1].val[10] * t[p << 1 | 1].val[11]) % MOD;
	t[p].val[13] = (t[p].val[13] + t[p << 1].val[11] * t[p << 1 | 1].val[10]) % MOD;
	t[p].val[14] = (t[p].val[14] + t[p << 1].val[10] * t[p << 1 | 1].val[13]) % MOD;
	t[p].val[14] = (t[p].val[14] + t[p << 1].val[12] * t[p << 1 | 1].val[10]) % MOD;
}

inline void build(int p, int l, int r) {
	if (l == r) {
		for (int i = 1; i <= 14; ++i) t[p].val[i] = 0;
		if (s[l] == '0') ++t[p].val[10];
		else if (s[l] == 'w') ++t[p].val[11];
		else if (s[l] == '(') ++t[p].val[1];
		else if (s[l] == ')') ++t[p].val[8];
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}

int main() {
	freopen("0w0.in", "r", stdin);
	freopen("0w0.out", "w", stdout);
	scanf("%d %d\n", &n, &m);
	scanf("%s\n", s + 1);
	char op, k; int x, y;
	for (int i = 1; i <= m; ++i) {
		scanf("%c ", &op);
		if (op == 'A') {
			scanf("%d %c\n", &x, &k);
			s[x] = k;
		} else if (op == 'B') {
			scanf("%d %d %c\n", &x, &y, &k);
			for (int i = x; i <= y; ++i) s[i] = k;
		} else {
			scanf("%d %d\n", &x, &y);
			build(1, x, y);
			printf("%lld\n", t[1].val[9]);
		}
	}
	fclose(stdin), fclose(stdout);
	return 0;
}

