# include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MAXN = 41;
const int P = 998244353;
int n, m, q, k;
int a[MAXN], b[MAXN];
int getdis(){
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += abs(a[i] - b[i]);
	return ans;
}
int ans = 0;
void dfs(int stp, int nd){
	if (nd > stp) return;
	if (stp == 0){
		ans++;
		return;
	}
	for (int i = 1; i <= n; i++){
		if (a[i - 1] >= a[i] + 1){
			int d1 = nd - abs(a[i] - b[i]) + abs(a[i] + 1 - b[i]);
			a[i]++;
			dfs(stp - 1, d1);
			a[i]--;
		}
		if (a[i] - 1 >= a[i + 1]){
			int d1 = nd - abs(a[i] - b[i]) + abs(a[i] - 1 - b[i]);
			a[i]--;
			dfs(stp - 1, d1);
			a[i]++;
		}
		if (a[i] == 0) break;
	}
}
int main(){
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> b[i];
	a[0] = b[0] = 1e9;
	n = (n + m + 20) / 2;
	cin >> q;
	while (q--){
		cin >> k;
		ans = 0;
		dfs(k, getdis());
		cout << ans << '\n';
	}
	return 0;
}
