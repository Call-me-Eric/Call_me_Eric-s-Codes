#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

int n, Q; 
int a[300005]; 
int le[300005], ri[300005]; 
i64 f[3005][3005]; 

int main(void) {
	freopen("seq.in", "r", stdin); 
	freopen("seq.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n >> Q; 
	for (int i = 1; i <= n; ++i) le[i] = n + 1;  
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; 
		le[a[i]] = min(le[a[i]], i); ri[a[i]] = max(ri[a[i]], i); 
	}
	for (int x = 1; x <= n; ++x) if (ri[x])
		for (int i = 1; i <= le[x]; ++i) f[i][ri[x]] = x; 
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			f[i][j] = max(f[i][j], f[i][j - 1]); 
	for (int len = 2; len <= n; ++len)
		for (int i = 1; i <= n - len + 1; ++i) {
			int j = i + len - 1; 
			f[i][j] += f[i][j - 1] + f[i + 1][j] - f[i + 1][j - 1]; 
		}
	while (Q--) {
		int l, r; cin >> l >> r; 
		cout << f[l][r] << "\n"; 
	}
	return 0; 
}
