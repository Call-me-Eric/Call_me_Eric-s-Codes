/*
每个节点有两个属性 编号和状态
建立超级源点连向每一层的 1 + n * (k - 1), 1 << k - 1
枚举层数 枚举状态 判状态对于当前层是否合法
然后连电梯 先判状态是否合法 从i层到j层是b[x][i]+a[x][j]
最后连同层的边
对于点n 额外向8n + 1, 0连边 
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9')
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

bool s1;

namespace steven24 {

const int N = 5050;
int a[505][10], b[505][10];
ll dis[N][521];
bool vis[N][521];
int n, k;

struct edge {
	int id, S, len;
}; 

vector<edge> v[505][10], e[N][521];

void build_map() {
	for (int i = 1; i <= k; ++i) e[0][0].push_back((edge){1 + (i - 1) * n, (1 << i - 1), a[1][i]});
	for (int j = 1; j <= k; ++j) {
		for (int s = 1; s < (1 << k); ++s) {
			if (!(s & (1 << j - 1))) continue;
			for (int t = 1; t <= k; ++t) {
				if (t == j) continue;
				if (s & (1 << t - 1)) continue;
//				cout << s << " " << t << " " << j << "\n";
				int tos = s ^ (1 << t - 1);
				for (int i = 1; i <= n; ++i) e[i + n * (j - 1)][s].push_back((edge){i + n * (t - 1), tos, a[i][t] + b[i][j]});
			}
			for (int i = 1; i <= n; ++i) {
				for (edge d : v[i][j]) e[i + n * (j - 1)][s].push_back((edge){d.id + n * (j - 1), s, d.len});
			}
			e[n + n * (j - 1)][s].push_back((edge){n * k + 1, 0, b[n][j]});
		}
	}
	return;
}

struct node {
	int id, s;
	ll dis;
	friend bool operator<(node x, node y) {
		return x.dis > y.dis;
	}
};
priority_queue<node> q;

void dijkstra() {
	memset(dis, 0x3f, sizeof dis);
	dis[0][0] = 0;
	q.push((node){0, 0, 0});
	while (!q.empty()) {
		int now = q.top().id, s = q.top().s;
		q.pop();
		if (vis[now][s]) continue;
		vis[now][s] = 1;
		for (edge i : e[now][s]) {
			int y = i.id, tos = i.S;
//			cout << now << " " << y << " " << s << " " << tos << "\n";
			if (dis[y][tos] > dis[now][s] + i.len) {
				dis[y][tos] = dis[now][s] + i.len;
				q.push((node){y, tos, dis[y][tos]});
			}
		}
	}
}

void main() {
	n = read(), k = read();
	for (int j = 1; j <= k; ++j) {
		for (int i = 1; i <= n; ++i) a[i][j] = read();
		for (int i = 1; i <= n; ++i) b[i][j] = read();
		int m = read();
		for (int i = 1; i <= m; ++i) {
			int x = read(), y = read(), z = read();
			v[x][j].push_back((edge){y, 0, z});
			v[y][j].push_back((edge){x, 0, z});
		}
	}
	
	build_map();
	dijkstra();
	
	printf("%lld\n", dis[n * k + 1][0]);
//	cout << dis[n + 4][3] << " " << dis[n + 3][3] << " " << dis[n + 2][3] << " " << dis[2][1] << "\n";
}

}

bool s2;

int main() {
	freopen("subway.in", "r", stdin);
	freopen("subway.out", "w", stdout);
	steven24::main();
//	cerr << (&s1 - &s2) * 1.0 / 1024 / 1024 << "\n";
	return 0;
}
