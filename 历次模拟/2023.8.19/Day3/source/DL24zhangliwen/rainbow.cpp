#include <bits/stdc++.h>
using namespace std; 

inline int read(void) {
	int x = 0, c = getchar(); 
	while (!isdigit(c)) c = getchar(); 
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x; 
}

int n, m; 
int a[2005][2005], g[2005][2005];  
bool buc[4000005]; 

int main(void) {
	freopen("rainbow.in", "r", stdin); 
	freopen("rainbow.out", "w", stdout); 
	n = read(), m = read(); 
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			a[i][j] = read(); g[i][j] = 1; 
			if (a[i][j] == a[i - 1][j - 1]) g[i][j] += g[i - 1][j - 1];  
		}
	unsigned int ans = 0; 
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {		
			int res = 1, mn = g[i][j], u = i - 1, v = j - 1; buc[a[i][j]] = 1; 
			while (u && v && mn > res) {
				if (a[i][v] == a[u][j] || buc[a[i][v]] || buc[a[u][j]]) break; 
				mn = min({mn, g[i][v] + res, g[u][j] + res}); 
				buc[a[i][v]] = buc[a[u][j]] = 1; 
				if (mn > res) ++res, --u, --v; 
			}
			ans += res; 
//			printf("%d %d %d\n", i, j, res); 
			for (int k = u; k <= i; ++k) buc[a[k][j]] = 0; 
			for (int k = v; k <= j; ++k) buc[a[i][k]] = 0; 
		}
	return !printf("%u\n", ans); 
}

/*
5 5
1 2 5 6 8
3 1 2 5 6
4 3 2 2 5
7 4 3 1 2
9 7 4 3 1
*/

// 同一条斜线上的满足点有单调性
// 按照斜线进行枚举 O(n)
// 斜线统计 O(n)
// 复杂度 O(n^3)  
