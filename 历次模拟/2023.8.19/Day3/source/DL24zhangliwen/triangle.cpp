#include <bits/stdc++.h>
using namespace std; 
const int NA = 0x3f3f3f3f; 

int n, k, a[105][105]; 
int f[105][105][10]; 

int main(void) {
	freopen("triangle.in", "r", stdin); 
	freopen("triangle.out", "w", stdout); 
	scanf("%d%d", &n, &k); 
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
			scanf("%d", &a[i][j]); 
	memset(f, 0x3f, sizeof f); 
	f[1][1][0] = a[1][1]; 
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= i; ++j) {
			vector<int> tmp; 
			for (int u = 0; u < k; ++u) if (j != i && f[i - 1][j][u] != NA) tmp.push_back(f[i - 1][j][u]); 
			for (int u = 0; u < k; ++u) if (j != 1 && f[i - 1][j - 1][u] != NA) tmp.push_back(f[i - 1][j - 1][u]); 
					
			sort(tmp.begin(), tmp.end(), greater<int>()); 
			for (int p = 0; p < k && p < tmp.size(); ++p)
				f[i][j][p] = tmp[p] + a[i][j]; 
		}
	vector<int> ans; 
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < k; ++j) 
			if (f[n][i][j] != NA) ans.push_back(f[n][i][j]); 
	sort(ans.begin(), ans.end(), greater<int>()); 
	printf("%d\n", ans[k - 1]);  
	return 0; 
}
