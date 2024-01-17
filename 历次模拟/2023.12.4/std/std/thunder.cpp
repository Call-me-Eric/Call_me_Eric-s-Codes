#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std; 
typedef long long i64; 
const i64 INF = 1e12; 

int n, tot, a[250005], b[250005];
i64 ans, dep[250005];
vector<pair<int, int>> G[250005];
__gnu_pbds::priority_queue<i64, greater<i64>> A[250005], B[250005]; 

void dfs(int x, int fa) {
    for (int i = a[x] + 1; i <= b[x]; ++i) // 不够
        A[x].push(dep[x] - INF), ++tot; 
    for (int i = b[x] + 1; i <= a[x]; ++i) // 够
        B[x].push(dep[x]); 
    for (auto [y, w] : G[x]) if (y != fa) {
        dep[y] = dep[x] + w, dfs(y, x); 
        A[x].join(A[y]), B[x].join(B[y]);
    }
    while (!A[x].empty() && !B[x].empty() && A[x].top() + B[x].top() < 2 * dep[x]) {
        i64 u = A[x].top(), v = B[x].top();
        A[x].pop(), B[x].pop(); ans += u + v - 2 * dep[x];
        A[x].push(2 * dep[x] - v), B[x].push(2 * dep[x] - u);
    }
}
int main(void) {
    freopen("thunder.in", "r", stdin); 
    freopen("thunder.out", "w", stdout); 
    
    ios::sync_with_stdio(0); 
    cin >> n; 
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w; 
        G[u].emplace_back(v, w); G[v].emplace_back(u, w); 
    }
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i]; 
    dfs(1, 0); 
    cout << ans + tot * INF << "\n"; 
    return 0; 
}