#include <bits/stdc++.h>
#define N 510

int n, m, k;
int fy[2][N * N], *x = *fy, *y = fy[1];

int one_line() {
	if (k == 1) return puts("-1"), 0;
	for (int i = 1; i < n + m; ++i) printf(n == 1 ? "1 %d\n" : "%d 1\n", i);
	return 0;
}

int main() {
	int i, j;
	scanf("%d%d%d", &n, &m, &k);
	if (n == 1 || m == 1) return one_line();
	if (k <= 2) return puts("-1"), 0;
	for (i = n; i; --i)
		for (j = m; j; --j)
			((i ^ j >> 1) & 1 ? x[++*x] : y[++*y]) = i << 16 | j;
	for (*x < *y ? std::swap(x, y) : (void)0; *x && *y; --*x, --*y)
		printf("%d %d\n%d %d\n", x[*x] >> 16, x[*x] & 65535, y[*y] >> 16, y[*y] & 65535);
	if (*x) printf("%d %d\n", x[*x] >> 16, x[*x] & 65535);
	return 0;
}
