#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using vi = vector<int>;
using pii = pair<int, int>;
#define pb emplace_back
#define sz(a) int(a.size())

int n, k;
string str;

signed main()
{
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k;
	str.resize(n, '0');
	if (n == k) {
		for (auto &c : str) {
			c = '1';
		}
		cout << str;
		return 0;
	}
	pii ans(0, n);
	auto calc = [&](int x) {
		ans = max(ans, make_pair((k / x) * x, x));
	} ;
	for (int i = 2; i <= n / i; ++i) {
		if (n % i == 0) {
			calc(i);
			calc(n / i);
		}
	}
	clog << ans.first << endl;
	int ct = k / ans.second, len = n / ans.second;
	for (int i = 0; i < n; i += len) {
		for (int j = i; j < i + ct; ++j) {
			str[j] = '1';
		}
	}
	cout << str;
	return 0;
}

