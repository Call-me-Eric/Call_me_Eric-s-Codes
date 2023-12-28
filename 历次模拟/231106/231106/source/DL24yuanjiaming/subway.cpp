#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define int long long
using namespace std;
constexpr int MAXK(10);
constexpr int MAXN(507);
constexpr int MAXM(1007);
constexpr int INF(0x3f3f3f3f3f3f3f3f);
int g[MAXK][MAXN][MAXN];
int f[MAXN][MAXM], vis[MAXN][MAXM];
int in[MAXK][MAXN], out[MAXK][MAXN];
int dis[MAXN], zd[MAXN];
int n, k, m, maxn, ans(INF), cnt;
struct node{
	int id, w;
	friend bool operator < (node x, node y) { return x.w > y.w; }
};
vector <node> e[MAXN];
priority_queue <node> q;
inline void read(int &temp) { cin >> temp; }
inline void Dijkstra(int x, int st) {
	memset(dis, 0x3f, sizeof(dis));
	memset(zd, 0, sizeof(zd));
	dis[st] = 0;
	q.push((node){st, 0});
	while (!q.empty()) {
		int u = q.top().id;
		q.pop();
		if (zd[u])  continue;
		zd[u] = 1;
		for (auto v : e[u]) {
			if (dis[v.id] > dis[u] + v.w) {
				dis[v.id] = dis[u] + v.w;
				q.push((node){v.id, dis[v.id]});
			}
		}
	}
	for (int i(1); i <= n; ++i)  g[x][st][i] = dis[i];  
}
signed main() {
	freopen("subway.in", "r", stdin);
	freopen("subway.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(k);
	for (int T(1); T <= k; ++T) {
		for (int i(1); i <= n; ++i)  read(in[T][i]);
		for (int i(1); i <= n; ++i)  read(out[T][i]);
		read(m);
		for (int i(1), u, v, w; i <= m; ++i)  read(u), read(v), read(w), e[u].push_back((node){v, w}), e[v].push_back((node){u, w});
		for (int i(1); i <= n; ++i)  Dijkstra(T, i);
		for (int i(1); i <= n; ++i)  e[i].clear();
	}
	maxn = (1 << k) - 1;
	memset(f, 0x3f, sizeof(f));
	f[1][0] = 0;
	for (int i(0); i <= maxn; ++i) {
		for (int j(1); j <= k; ++j) {
			if ((i | (1 << (j - 1))) != i)  continue;
			for (int u(1); u <= n; ++u) {
				for (int v(1); v <= n; ++v) {
					f[v][i] = min(f[v][i], f[u][i ^ (1 << (j - 1))] + in[j][u] + out[j][v] + g[j][u][v]);
					if (v == n)  ans = min(ans, f[v][i]);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
