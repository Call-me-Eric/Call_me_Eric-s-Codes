#include <iostream>
using namespace std;
constexpr int MAXN = 2007;
struct node{ int x1, y1, x2, y2; }a[MAXN];
int ansx[MAXN][MAXN], ansy[MAXN][MAXN], vis[MAXN][MAXN];
int cnt[MAXN];
int xx[4] = {0, 1, 0, -1};
int yy[4] = {1, 0, -1, 0};
int n, m;
inline void read(int &temp) { cin >> temp; }
void dfs(int now, int x, int y) {
	if (x == a[now].x2 && y == a[now].y2) {
		if (now == m) {
			for (int i = 1; i <= m; ++i) {
				cout << cnt[i] << endl;
				for (int j = 1; j <= cnt[i]; ++j)  cout << ansx[i][j] << " " << ansy[i][j] << endl;
			}
			exit(0);
		}
		vis[a[now + 1].x1][a[now + 1].y1] = 0, ++cnt[now + 1];
		ansx[now + 1][cnt[now + 1]] = a[now + 1].x1, ansy[now + 1][cnt[now + 1]] = a[now + 1].y1;
		dfs(now + 1, a[now + 1].x1, a[now + 1].y1);
		vis[a[now + 1].x1][a[now + 1].y1] = 1, --cnt[now + 1];
		return ;
	}
	if (x < 1 || x > n || y < 1 || y > n || vis[x][y])  return ;
	for (int i = 0; i < 4; ++i) {
		int nx = x + xx[i], ny = y + yy[i];
		vis[nx][ny] = 1, ++cnt[now];
		ansx[now][cnt[now]] = nx, ansy[now][cnt[now]] = ny;
		dfs(now, nx, ny);
		vis[nx][ny] = 1, --cnt[now];
	}
}
int main() {
	freopen("flowfree.in", "r", stdin);
	freopen("flowfree.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m);
	for (int i = 1; i <= m; ++i)  read(a[i].x1), read(a[i].y1), read(a[i].x2), read(a[i].y2), vis[a[i].x1][a[i].y1] = 1, vis[a[i].x2][a[i].y2] = 1;
	vis[a[1].x1][a[1].y1] = 0, ++cnt[1];
	ansx[1][cnt[1]] = a[1].x1, ansy[1][cnt[1]] = a[1].y1;
	dfs(1, a[1].x1, a[1].y1);
	return 0;
}
/*
2 2
1 1 2 1
1 2 2 2
*/
