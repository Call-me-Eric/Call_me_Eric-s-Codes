#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 105;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, k;
int f[N][N][M];
int a[N][N];
int b[N], tot;
bool cmp(int a, int b) {
	return a > b;
}
signed main() {
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	n = read(), k = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++) a[i][j] = read();
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int K = 1; K <= 10; K++) f[i][j][K] = -inf;
	f[1][1][1] = a[1][1];
	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= i; j++) {
			tot = 0;
			for(int K = 1; K <= 10; K++) b[++tot] = f[i - 1][j - 1][K], b[++tot] = f[i - 1][j][K];
			sort(b + 1, b + 1 + tot, cmp);
			for(int K = 1; K <= 10; K++)
				if(b[K] != -inf) f[i][j][K] = a[i][j] + b[K];
		}
	tot = 0;
	for(int j = 1; j <= n; j++)
		for(int i = 1; i <= 10; i++) b[++tot] = f[n][j][i];
	sort(b + 1, b + 1 + tot, cmp);
	printf("%lld\n", b[k]);
	return 0;
}
/*
8:26
*/

