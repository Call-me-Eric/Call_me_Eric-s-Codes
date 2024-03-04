#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e6 + 0721;
ll f[N][3];
int c[N];
int head[N], to[N << 1], nxt[N << 1], cnt;
int n;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

inline void add_edge(int x, int y) {
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}

void dfs(int x, int fa) {
	f[x][1] = c[x];
//	bool flag = 1;
	ll minn = 0x3f3f3f3f3f3f3f3f;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
//		cout << x << " " << y << "\n";
		if (y == fa) continue;
//		flag = 0;
		dfs(y, x);
		f[x][0] += min(f[y][1], f[y][2]);
		f[x][1] += min(f[y][0], min(f[y][1], f[y][2]));
		f[x][2] += min(f[y][1], f[y][2]);
		minn = min(minn, f[y][1] - f[y][2]);
	}
//	cout << x << " " << f[x][0] << " " << f[x][1] << " " << f[x][2] << "\n";
	if (minn >= 0) f[x][2] += minn;
}

int main() {
	freopen("router.in", "r", stdin);
	freopen("router.out", "w", stdout);
	
	n = read();
	for (int i = 1; i <= n; ++i) c[i] = read();
	for (int i = 1; i < n; ++i) {
		int x, y;
		x = read(), y = read();
		add_edge(x, y);
		add_edge(y, x);
	}
	
	dfs(1, 0);
	
	printf("%lld", min(f[1][1], f[1][2]));
	
	return 0;
} 
/*
4
1 17 13 4
1 2
1 3
3 4
*/
