#include<bits/stdc++.h>
using namespace std;

int n, m;

int dx[] = {0, 0, 0, 1, -1};
int dy[] = {0, 1, -1, 0, 0};

struct node {
	int x1, y1, x2, y2;
} a[15];

int vis[15][15];
vector<pair<int, int>> ans[15];

struct Node {
	int x, y;
	int vis[15][15];
	vector<pair<int, int>> p;
	Node() {
		memset(vis, 0, sizeof(vis));
	}
};

void dfs(int id) {
	if (id > n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!vis[i][j]) {
					return;
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			cout << ans[i].size() << '\n';
			for (auto v : ans[i]) {
				cout << v.first << ' ' << v.second << '\n';
			}
		}
		exit(0);
	}
	queue<Node >q;
	Node s;
	s.x = a[id].x1;
	s.y = a[id].y1;
	memcpy(s.vis, vis, sizeof(vis));
	if (s.vis[s.x][s.y]) {
		return;
	}
	s.vis[s.x][s.y] = 1;
	s.p.push_back({s.x, s.y});
	q.push(s);
	while (!q.empty()) {
		Node t = q.front();
		q.pop();
		if (t.x == a[id].x2 && t.y == a[id].y2) {
			memcpy(vis, t.vis, sizeof(t.vis));
			ans[id] = t.p;
			dfs(id + 1);
			continue;
		}
		for (int i = 1; i <= 4; i++) {
			int tx = t.x + dx[i], ty = t.y + dy[i];
			if (tx < 1 || tx > n || ty < 1 || ty > n || t.vis[tx][ty]) {
				continue;
			}
			Node tt;
			tt.x = tx, tt.y = ty;
			tt.p = t.p;
			tt.p.push_back({tx, ty});
			memcpy(tt.vis, t.vis, sizeof(t.vis));
			tt.vis[tx][ty] = 1;
			q.push(tt);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("flowfree.in", "r", stdin);
	freopen("flowfree.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
	}
	dfs(1);
	return 0;
}

