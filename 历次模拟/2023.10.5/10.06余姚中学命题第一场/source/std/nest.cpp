#include <bits/stdc++.h>
using namespace std;
#define P 1000000007
int n, a[5005], now[5005], f[5005], g[5005][5005];
int R(int x, int y) { return (x += y) >= P ? x - P : x; }
int main() {
	freopen ("nest.in", "r", stdin);
	freopen ("nest.out", "w", stdout);
	cin >> n;
	for (int i=1; i<=n; i++)
		scanf ("%d", &a[i]);
	for (int i=1; i<=n+1; i++) {
		g[i][i] = 1;
		for (int j=i-1; j; j--) {
			g[i][j] = g[i][j+1];
			if (a[j] ^ a[i]) g[i][j] = R(g[i][j], R(g[i][j+1], now[a[j]] ? P - g[i][now[a[j]]+1] : 0));
			now[a[j]] = j;
		}
		for (int j=i-1; j; j--)
			now[a[j]] = 0;
	}
	f[0] = 1;
	for (int i=1; i<=n+1; i++) {
		for (int j=0; j<i; j++)
			f[i] = (f[i] + 1ll * (g[i][j+1] + P - g[now[a[i]]][j+1]) * f[j]) % P;
		now[a[i]] = i;
	}
	cout << f[n+1];
}
