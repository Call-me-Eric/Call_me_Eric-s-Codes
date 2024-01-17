#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

int n; 
i64 L, R; 
int a[200005]; 

int main(void) {
	freopen("game.in", "r", stdin); 
	freopen("game.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n >> L >> R; 
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	sort(a + 1, a + n + 1); 
	i64 s1 = 0, s2 = 0; 
	for (int i = 1; i <= n; i += 2) s1 += a[i], s2 += a[i + 1]; 
	if (s1 < L || s2 > R) cout << "Alice\n"; 
	else cout << "Bob\n"; 
	return 0; 
}
