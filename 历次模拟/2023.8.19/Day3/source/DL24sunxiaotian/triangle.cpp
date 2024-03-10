#include <bits/stdc++.h>
using namespace std;

int f[101][101][21], a[101][101];
int n, k;
int ans[0x0d00];

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9')
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

inline bool cmp(int x, int y) {
	return x > y;
}

void dp() {
	f[1][1][1] = a[1][1];
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			for (int s = 1; s <= 10; ++s) {
				f[i][j][s] = f[i - 1][j - 1][s] + a[i][j];
				f[i][j][s + 10] = f[i - 1][j][s] + a[i][j];
			}
			sort(f[i][j] + 1, f[i][j] + 21, cmp);
		}
	}
}

int main() {
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	
	n = read(), k = read();
	memset(f, -0x3f, sizeof f);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) a[i][j] = read();
	}

	dp();
	
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= 10; ++j) ans[++top] = f[n][i][j];
	}
	
	sort(ans + 1, ans + 1 + top, cmp);
	printf("%d", ans[k]);
	
	return 0;
}
/*
3 2
1
1 1
1 2 1
*/
