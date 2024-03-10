#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 2e6 + 6;
const int M = 20;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n;
vector<int>a[N];
int b[N], tot;
int lim = INT_MAX;
signed main() {
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) {
		int tot;
		tot = read();
		for(int j = 1; j <= tot; j++) a[i].push_back(read());
		sort(a[i].begin(), a[i].end());
		lim = min(lim, a[i][a[i].size() - 1]);
	}
	int ans = INT_MAX;
	for(int i = 1; i <= n; i++)
		for(auto mn : a[i]) {
			if(mn > lim) continue;
			int res = 0;
			for(int j = 1; j <= n; j++)
				if(i != j) {
					tot = 0;
					for(auto v : a[j]) b[++tot] = v;
					if(mn > b[tot]) {
						res = INT_MAX;
						break;
					}
					int pos = lower_bound(b + 1, b + 1 + tot, mn) - b;
					res = max(res, b[pos] - mn);
				}
			ans = min(ans, res);
		}
	printf("%lld\n", ans);
	return 0;
}
/*
8:26
*/

