#include <bits/stdc++.h>
using namespace std; 

int n, m, k, L; 
int x[10005], y[10005]; 
int p[10005], vis[10005]; 
vector<int> road; 
string d[10005], _0, _1; 
inline string calc(string &a, string &b) {
    string c = _0; 
    for (int i = L - 1; i >= 0; --i) c[i] = a[i] - '0' + b[i]; 
    for (int i = L - 1; i >= 1; --i)
        if (c[i] > '1') ++c[i - 1], c[i] -= 2; 
    return c; 
}
void findPath(int i) {
    road.emplace_back(i); 
    if (i != 1) findPath(p[i]); 
}

int main(void) {
    freopen("distance.in", "r", stdin); 
    freopen("distance.out", "w", stdout); 
    ios::sync_with_stdio(0); 
    cin >> n >> m >> k; L = max(n, m) + 2; 
    for (int i = 1; i <= k; ++i) cin >> x[i] >> y[i]; 
    for (int i = 0; i < L; ++i) _0 = _0 + '0', _1 = _1 + '1'; 
    for (int i = 2; i <= k; ++i) d[i] = _1; 
    #define psi pair<string, int> 
    priority_queue<psi, vector<psi>, greater<psi>> q;    
    q.emplace(d[1] = _0, 1); 
    while (!q.empty()) {
        int u = q.top().second; q.pop(); 
        if (vis[u]) continue; vis[u] = 1; 
        for (int v = 1; v <= k; ++v) if (u != v) {
            int w = max(abs(x[u] - x[v]), abs(y[u] - y[v])); 
            _0[L - w - 1] = '1'; 
            string now = calc(d[u], _0); 
            if (d[v] > now) p[v] = u, q.emplace(d[v] = now, v); 
            else if (d[v] == now && u < p[v]) p[v] = u; 
            _0[L - w - 1] = '0'; 
        }
    }
    // for (int i = 1; i <= k; ++i) 
        // cout << p[i] << " " << d[i] << "\n"; 
    findPath(k); 
    cout << road.size() << "\n"; reverse(road.begin(), road.end()); 
    for (int i : road) cout << i << " "; 
    cout << "\n"; 
    // cout << calc(d[2], d[2]) << "\n"; 
    return 0; 
}