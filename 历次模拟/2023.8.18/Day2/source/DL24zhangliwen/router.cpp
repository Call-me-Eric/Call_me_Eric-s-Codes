#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

inline int read(void) {
	int x = 0, c = getchar(); 
	while (!isdigit(c)) c = getchar(); 
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x; 
}

int n, a[1000005];  
vector<int> G[1000005]; 
i64 f[1000005][3]; 

void dfs(int x, int fa) {
	f[x][0] += a[x]; 
	bool is1 = 0; i64 mn1 = 1e18; 
	for (int y : G[x]) if (y != fa) {
		dfs(y, x); 
		f[x][0] += min({f[y][0], f[y][1], f[y][2]}); 
		
		if (f[y][0] <= f[y][1]) f[x][1] += f[y][0], is1 = 1; 
		else f[x][1] += f[y][1]; 
		mn1 = min(mn1, f[y][0] - f[y][1]); 
		
		f[x][2] += min(f[x][0], f[x][1]); 
	}
	if (!is1) f[x][1] += mn1; 
}

int main(void) {
	freopen("router.in", "r", stdin); 
	freopen("router.out", "w", stdout); 
	n = read(); 
	for (int i = 1; i <= n; ++i) a[i] = read(); 
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(); 
		G[u].emplace_back(v); G[v].emplace_back(u); 
	} dfs(1, 0); 
	printf("%lld\n", min({f[1][0], f[1][1], f[1][2]})); 
	return 0; 
}
