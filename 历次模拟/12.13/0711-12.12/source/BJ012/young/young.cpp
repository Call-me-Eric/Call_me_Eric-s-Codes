#include <bits/stdc++.h>
using namespace std;
constexpr int N = 45, maxn = 40, inf = 1e9, mod = 998244353;
using arr = array<int, N>;
int n, m, q, k, a[N], b[N];
int add(int a, int b) {return a += b - mod, a += a >> 31 & mod;}
void upd(int &a, int b) {a += b - mod, a += a >> 31 & mod;}
void work(int *seq, int n, map<arr, int> &ans, int k) {
	arr st{};
	for(int i = 1; i <= n; i ++) st[i] = seq[i];
	st[0] = inf;
	map<arr, int> dp, new_dp;
	dp[st] = 1;
	for(int i = 1; i <= k; i ++) {
		new_dp.clear();
		for(auto [sta, w] : dp) {
			for(int i = 1; i <= maxn; i ++) {
				if(sta[i] < sta[i - 1]) {
					arr nxt = sta;
					nxt[i] ++;
					upd(new_dp[nxt], w);
				}
			}
			for(int i = 1; i <= maxn; i ++) {
				if(sta[i] > sta[i + 1]) {
					arr nxt = sta;
					nxt[i] --;
					upd(new_dp[nxt], w);
				}
			}
		}
		swap(dp, new_dp);
	}
	ans = dp;
}
int main() {
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	cin >> m;
	for(int i = 1; i <= m; i ++) cin >> b[i];
	cin >> q >> k;
	int sum = accumulate(a + 1, a + n + 1, 0) - accumulate(b + 1, b + m + 1, 0);
	if(sum % 2 != k % 2) {
		cout << 0 << '\n';
		return 0;
	}
	map<arr, int> dp1, dp2;
	work(a, n, dp1, k / 2), work(b, m, dp2, (k + 1) / 2);
	int ans = 0;
	for(auto [sta, w] : dp1) {
		if(dp2.count(sta)) {
			upd(ans, 1ll * w * dp2[sta] % mod);
		}
	}
	cout << ans << '\n';
	return 0;
}