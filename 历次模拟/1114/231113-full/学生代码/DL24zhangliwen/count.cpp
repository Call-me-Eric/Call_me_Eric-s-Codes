#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 
const int INF = 1e9; 

inline int poww(int a, int b) {
	int r = 1; 
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
	return r; 
}

int n; 
int a[500005], b[500005]; 
bool isb[500005]; 
int ti[500005]; 
set<int> pos[500005];  
set<pair<int, int>> s; // ti, val

int main(void) {
	freopen("count.in", "r", stdin); 
	freopen("count.out", "w", stdout); 
	ios::sync_with_stdio(0); 
	
	cin >> n; 
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	for (int i = 1; i <= n; ++i) cin >> b[i]; 
	int B = 1; 
	for (int i = 1; i <= n; ++i) if (a[i] == b[i]) {
		if (isb[a[i]]) return cout << poww(n, n) << "\n", 0; 
		isb[a[i]] = 1; B = 1ll * B * n % P; 
	}
	for (int i = 1; i <= n; ++i) {
		if (!isb[a[i]]) ++ti[a[i]], pos[a[i]].emplace(i); 
		if (!isb[b[i]]) ++ti[b[i]], pos[b[i]].emplace(i); 
	}
	for (int i = 1; i <= n; ++i) if (!isb[i]) s.emplace(ti[i], i); 
	while (!s.empty()) {
		auto u = *s.begin(); s.erase(s.begin()); 
//		cerr << u.first << " " << u.second << "\n"; 
		if (u.first == 0) return cout << poww(n, n) << "\n", 0; 
		else if (u.first == 2) return cout << (poww(n, n) - 2ll * B % P + P) % P << "\n", 0; 
		else {
			int x = u.second; 
			int p = *pos[x].begin(), v = -1; 
			if (a[p] == x) v = b[p]; 
			else v = a[p]; 
//			assert(v != -1); 
			if (!isb[v]) {
//				cerr << "DEL " << v << " " << p << "\n"; 
				s.erase(make_pair(ti[v], v)); --ti[v]; 
//				assert(pos[v].find(p) != pos[v].end()); 
				pos[v].erase(p); 
				s.emplace(ti[v], v); 
			}
		}
	}
	
	cout << (poww(n, n) - B + P) % P << "\n"; 	
	return 0; 
}
