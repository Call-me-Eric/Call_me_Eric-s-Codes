#include <bits/stdc++.h>
using namespace std;

const long long mod = 998244353;
const int N = 1505;

long long mtx[N][N], cur[N], a[N][N], ans[N];
bool exi[N];
int n, q, idx[N], lst[N], nxt[N], z[N], prv[N];

inline long long Power(long long x, long long y) {
	//cnt++;
	long long ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

inline void Ins(long long *cur, int tim) {
	for (int i = 1;i <= n + 1;i++) {
		if (cur[i]) {
			if (!mtx[i][i]) {
				long long inv = Power(cur[i], mod - 2);
				for (int j = i;j <= n + 1;j++) mtx[i][j] = cur[j] * inv % mod;
				idx[i] = tim;
				return;
			} else {
				if (nxt[tim] > nxt[idx[i]]) {
					swap(tim, idx[i]);
					long long inv = Power(cur[i], mod - 2);
					for (int j = i;j <= n + 1;j++) cur[j] = cur[j] * inv % mod;
					for (int j = i;j <= n + 1;j++) swap(mtx[i][j], cur[j]);
				}
				long long tmp = cur[i];
				for (int j = i;j <= n + 1;j++) cur[j] = (cur[j] - tmp * mtx[i][j] % mod + mod) % mod;
			}
		}
	}
}

inline void Read() {
	cin >> n >> q;
	for (int i = 1;i <= n;i++) {
		z[i] = i;
		for (int j = 1;j <= n + 1;j++) cin >> a[i][j];
		lst[i] = i;
		nxt[i] = n + q + 1;
		exi[i] = 1;
		for (int j = 1;j <= n + 1;j++) cur[j] = a[i][j];
	}
}

inline void Answer() {
	//for (int i = 1;i <= n + 1;i++) cout << idx[i] << " ";
	//cout << endl;
	if (exi[idx[n + 1]] && mtx[n + 1][n + 1]) {
		cout << "No\n";
		return;
	}
	for (int i = 1;i <= n;i++) {
		if (mtx[i][i] % mod == 0 || !exi[idx[i]]) {
			cout << "Many\n";
			return;
		}
	}
	for (int i = n;i >= 1;i--) {
		ans[i] = mtx[i][n + 1];
		int j;
		for (j = i + 1;j + 8 <= n;j += 8) {
			//ans[i] = (ans[i] - ans[j] * mtx[i][j]) % mod;
			ans[i] -= ans[j + 0] * mtx[i][j + 0];
			ans[i] -= ans[j + 1] * mtx[i][j + 1];
			ans[i] -= ans[j + 2] * mtx[i][j + 2];
			ans[i] -= ans[j + 3] * mtx[i][j + 3];
			ans[i] -= ans[j + 4] * mtx[i][j + 4];
			ans[i] -= ans[j + 5] * mtx[i][j + 5];
			ans[i] -= ans[j + 6] * mtx[i][j + 6];
			ans[i] -= ans[j + 7] * mtx[i][j + 7];
			ans[i] %= mod;
		}
		for (;j <= n;j++) {
			ans[i] = (ans[i] - ans[j] * mtx[i][j]) % mod;
		}
	}
	for (int i = 1;i <= n;i++) cout << (ans[i] % mod + mod) % mod << " ";
	cout << "\n";
}

inline void Solve() {
	for (int i = n + 1;i <= n + q;i++) {
		cin >> z[i];
		for (int j = 1;j <= n + 1;j++) cin >> a[i][j];
		prv[i] = lst[z[i]];
		nxt[lst[z[i]]] = i;
		lst[z[i]] = i;
		nxt[i] = n + q + 1;
	}
	//for (int i = 1;i <= n + q;i++) cout << nxt[i] << " ";
	//cout << endl;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n + 1;j++) cur[j] = a[i][j];
		Ins(cur, i);
	}
	Answer();
	for (int t = n + 1;t <= n + q;t++) {
		exi[prv[t]] = 0;
		exi[t] = 1;
		for (int i = 1;i <= n + 1;i++) {
			cur[i] = a[t][i];
		}
		Ins(cur, t);
		Answer();
	}
}

int main() {
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Read();
	Solve();
	return 0;
}
