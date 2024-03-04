#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

const int N = 100;

int n, k, a[N + 5][N + 5];

struct node {
	int mx[10];
	void ins(int v) {
		for(int i = 0; i < 10; i++) {
			if(v >= mx[i]) {
				for(int j = 9; j > i; j--) {
					mx[j] = mx[j - 1];
				}
				mx[i] = v;
				break;
			}
		}
	}
};

node f[N + 5][N + 5];

int main() {
	freopen("triangle.in", "r", stdin), freopen("triangle.out", "w", stdout);

	n = rd(), k = rd();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			a[i][j] = rd();
		}
	}

	memset(f, -63, sizeof(f)), f[0][0].ins(0);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			for(int p = 0; p < 10; p++) {
				f[i][j].ins(f[i - 1][j].mx[p] + a[i][j]);
				f[i][j].ins(f[i - 1][j - 1].mx[p] + a[i][j]);
			}
		}
	}
	node ans; memset(&ans, -63, sizeof(node));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i; j++) {
			for(int p = 0; p < 10; p++) {
				ans.ins(f[i][j].mx[p]);
			}
		}
	}
	printf("%d\n", ans.mx[k - 1]);
	return 0;
}

