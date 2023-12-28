#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int N = 700 + 5, mod = 998244353;
int n, q;
int las[N], pw[N];
bool vis[N], bk[20][N];
int a[N << 1][N];
int cur[N][N];
int back[20][N][N], tx;
vector<int> qst[N << 2];
void cg(int nd, int l, int r, int y, int L, int R) {
	if (l <= L && r >= R) return qst[nd].push_back(y), void();
	const int mid = L + R >> 1;
	if (l <= mid) cg(nd << 1, l, r, y, L, mid);
	if (r > mid) cg(nd << 1 | 1, l, r, y, mid + 1, R);
}
int ksm(int b, int e) {
	int res = 1;
	while (e) {
		if (e & 1) res = 1ll * res * b % mod;
		b = 1ll * b * b % mod;
		e >>= 1;
	}
	return res;
}
void proc(int x) {
	int * c = a[x], px = 1;
	while (cur[px][px]) ++ px;
	memcpy(cur[px], c, sizeof cur[px]);
	c = cur[px];
	for (int i = 1; i <= n; ++ i) {
		if (i == px || !cur[i][i] || !c[i]) continue;
		int j = 1; long long w = c[i];
		for (j = 1; j + 6 <= n; j += 8) {
			if (j <= i && j + 7 >= i) {
				for (int k = j; k <= j + 7; ++ k) {
					if (k == i) continue;
					int & p = c[k];
					p = (p - cur[i][k] * w) % mod;
					// if (p < 0) p += mod;
				}
				continue;
			}
			c[j] = (c[j] - cur[i][j] * w) % mod;
			c[j + 1] = (c[j + 1] - cur[i][j + 1] * w) % mod;
			c[j + 2] = (c[j + 2] - cur[i][j + 2] * w) % mod;
			c[j + 3] = (c[j + 3] - cur[i][j + 3] * w) % mod;
			c[j + 4] = (c[j + 4] - cur[i][j + 4] * w) % mod;
			c[j + 5] = (c[j + 5] - cur[i][j + 5] * w) % mod;
			c[j + 6] = (c[j + 6] - cur[i][j + 6] * w) % mod;
			c[j + 7] = (c[j + 7] - cur[i][j + 7] * w) % mod;
		}
		for (; j <= n + 1; ++ j) {
			if (j == i) continue;
			int & p = c[j];
			p = (p - cur[i][j] * w) % mod;
			// if (p < 0) p += mod;
		}
		c[i] = 0;
	}
	// cout << px << "===\n";
	// for (int i = 1; i <= n; ++ i) 
	// 	for (int j = 1; j <= n + 1; ++ j) 
	// 		cout << cur[i][j] << " \n"[j == n + 1];
	if (!c[px]) {
		for (int i = px; i <= n; ++ i) 
			if (c[i] && !cur[i][i]) {
				swap(cur[px], cur[i]); c = cur[i];
				px = i; break;
			}
		// return;
	}
	int inv = ksm(c[px], mod - 2);
	if (inv == 0) inv = 1;
	for (int i = px; i <= n + 1; ++ i) 
		c[i] = 1ll * c[i] * inv % mod;
	for (int i = 1; i <= n; ++ i) {
		if (i == px || !cur[i][i] || !cur[i][px]) continue;
		for (int j = px + 1; j <= n + 1; ++ j) {
			int & p = cur[i][j];
			p = (p - 1ll * c[j] * cur[i][px]) % mod;
			// if (p < 0) p += mod;
		}
		cur[i][px] = 0;
	}
	// cout << px << "===\n";
	// for (int i = 1; i <= n; ++ i) 
	// 	for (int j = 1; j <= n + 1; ++ j) 
	// 		cout << cur[i][j] << " \n"[j == n + 1];
}
void solve(int nd, int l, int r) {
	// cout << nd << " " << l << " " << r << "qwq\n";
	int tw = ++ tx;
	int fl = qst[nd].empty();
	if (!fl) memcpy(back[tw], cur, sizeof back[tw]);
	// memcpy(bk[tw], vis, sizeof bk[tw]);
	// memcpy(b1[tw], pos, sizeof b1[tw]);
	// memcpy(b2[tw], path, sizeof b2[tw]);
	for (int i : qst[nd]) proc(i);
	if (l == r) {
		int fl1 = 0, fl2 = 0;
		for (int i = 1; i <= n; ++ i) 
			fl1 |= cur[i][i] == 0 && cur[i][n + 1] != 0, fl2 |= cur[i][i] == 0;
		if (fl1) cout << "No\n";
		else if (fl2) cout << "Many\n";
		else for (int i = 1; i <= n; ++ i) 
			cout << (cur[i][n + 1] + mod) % mod << " \n"[i == n];
	} else {
		const int mid = l + r >> 1;
		solve(nd << 1, l, mid); solve(nd << 1 | 1, mid + 1, r);
	}
	-- tx;
	if (!fl) memcpy(cur, back[tw], sizeof back[tw]);
	// memcpy(vis, bk[tw], sizeof bk[tw]);
	// memcpy(pos, b1[tw], sizeof b1[tw]);
	// memcpy(path, b2[tw], sizeof b2[tw]);
	// cout << px << "???\n";
	// for (int i = 1; i <= n; ++ i) 
	// 	for (int j = 1; j <= n + 1; ++ j) 
	// 		cout << cur[i][j] << " \n"[j == n + 1];
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i) {
		las[i] = 1; pw[i] = i;
		for (int j = 1; j <= n + 1; ++ j) 
			cin >> a[i][j];
	}
	++ q;
	for (int i = 2; i <= q; ++ i) {
		int pos; cin >> pos;
		cg(1, las[pos], i - 1, pw[pos], 1, q);
		int k = i + n - 1; pw[pos] = k; las[pos] = i;
		for (int j = 1; j <= n + 1; ++ j) 
			cin >> a[k][j];
	}
	for (int i = 1; i <= n; ++ i) 
		cg(1, las[i], q, pw[i], 1, q);
	solve(1, 1, q);
	return 0;
}