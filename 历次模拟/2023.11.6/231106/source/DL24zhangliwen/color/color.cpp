#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 

int n, k, a[1005]; 
int f[1005][1005]; 
vector<int> G[1005]; 

void dfs(int x, int fa) {
	if (a[x]) f[x][a[x]] = 1; 
	else for (int i = 1; i <= k; ++i) f[x][i] = 1; 
	for (int y : G[x]) if (y != fa) {
		dfs(y, x); 
		if (a[x]) f[x][a[x]] = 1ll * f[x][a[x]] * (f[y][0] - f[y][a[x]] + P) % P; 
		else {
			for (int i = 1; i <= k; ++i) 
				f[x][i] = 1ll * f[x][i] * (f[y][0] - f[y][i] + P) % P; 
		} 
	}
	for (int i = 1; i <= k; ++i) f[x][0] = (f[x][0] + f[x][i]) % P; 
}

int main(void) {
	freopen("color.in", "r", stdin); 
	freopen("color.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n >> k; 
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v; 
		G[u].emplace_back(v); G[v].emplace_back(u); 
	}
	dfs(1, 0); 
	cout << f[1][0] << "\n"; 
	return 0; 
}
