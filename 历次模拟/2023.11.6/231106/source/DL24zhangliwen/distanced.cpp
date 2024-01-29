#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

int n, t; 
struct Car {
	int x, a; 
	bool operator< (const Car &a) const {
		return x < a.x; 
	}
} a[100005]; 

i64 ans[100005]; 
bool ch[25]; 
void dfs(int x) {
	if (x > n) {
		i64 v = 0; 
		for (int i = 1; i <= n; ++i) if (ch[i]) v += a[i].a; 
		i64 c = 0, lst = -2e9 - 5; 
		for (int i = 1; i <= n; ++i) if (ch[i]) {
			if (a[i].x - lst > t) ++c; 
			lst = a[i].x; 
		}
		ans[c] = max(ans[c], v); 
		return; 
	}
	ch[x] = 1; dfs(x + 1); 
	ch[x] = 0; dfs(x + 1); 
} 

int main(void) {
	freopen("distanced.in", "r", stdin); 
	freopen("distanced.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n >> t; 
	for (int i = 1; i <= n; ++i) cin >> a[i].x; 
	for (int i = 1; i <= n; ++i) cin >> a[i].a; 
	sort(a + 1, a + n + 1); 
	dfs(1); 
	for (int i = 1; i <= n; ++i) ans[i] = max(ans[i], ans[i - 1]); 
	for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n]; 
	return 0; 
}
