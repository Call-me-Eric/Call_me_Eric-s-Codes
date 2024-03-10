//假的 骗分用的 
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 4e6 + 6;
const int M = 2002;

bool vis[M][M], viss[N];
int a[M][M], id[M][M];
int n, m, tot;
ll ans;

struct node {
	int xs, xe, len;
	int end;
} lian[N];

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 3) + (xr << 1) + (cr ^ 48);
	return xr * F;
}

void init() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (vis[i][j]) continue;
			lian[++tot].xs = i;
			lian[tot].end = i;
			lian[tot].len = 1;
			id[i][j] = tot;
			for (int k = 1; k + i <= n && k + j <= m; ++k) {
				if (a[i + k][j + k] == a[i + k - 1][j + k - 1]) {
					vis[i + k][j + k] = 1;
					id[i + k][j + k] = tot;
					lian[tot].end = i + k;
					++lian[tot].len;
				} else
					break;
			}
		}
	}
}

void splay(int i, int j, int k) {
	vis[i][j] = 1;
	int maxn = lian[id[i][j]].end - i;
//	cout << id[i][j] << " " << lian[id[i][j]].end << " " << maxn << "\n";
//	viss[a[i][j]] = 1;
	for (; k <= maxn; ++k) {
//		cout << maxn << "\n";
//		cout << a[i][j + k] << " " << viss[a[i][j + k]] << " " << a[i + k][j] << " " << viss[a[i + k][j]] << "\n";
		if (a[i][j + k] == a[i + k][j]) break;
		if (viss[a[i][j + k]]) {
//			--k;
			break;
		}
		maxn = min(maxn, k + lian[id[i][j + k]].end - i);
		if (viss[a[i + k][j]]) {
//			--k; 
			break;
		}
		viss[a[i + k][j]] = 1;
		viss[a[i][j + k]] = 1;
		maxn = min(maxn, k + lian[id[i + k][j]].end - (i + k));
	}
//	cout << k << "\n";
	--k;
	ans += k + 1;
	viss[a[i + k][j]] = viss[a[i][j + k]] = 0;
//	cout << "ans: " <<  i << " " << j << " " << ans << " " << k << "\n";
	if (i < lian[id[i][j]].end && k) splay(i + 1, j + 1, k);
}

void solve() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
//			cout << i << " " << j << " " << ans << "\n";
			if (vis[i][j]) continue;
			splay(i, j, 1);
		}
	}
}

int main() {
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) scanf("%d", &a[i][j]);
	}
	
	init();
//	cout << "---\n";
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 1; j <= m; ++j) cout << id[i][j] << " ";
//		cout << endl;
//	}
	memset(vis, 0, sizeof vis);
	solve();
	
	printf("%lld", ans);
	
	return 0;
}
