//假的 骗分用的 
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 6;
vector<int> v[N];
struct country {
	int c, id;
	friend bool operator<(country x, country y) {
		return x.c < y.c;
	}
} c[N];
struct node {
	int maxn, minn, jc;
	bool ok;
} a[N];
int n;

inline int read() {
	int xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9') if (cr == '-') F = -1;
	while (cr >= '0' && cr <= '9') 
		xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

int main() {
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	
	n = read();
	for (int i = 1; i <= n; ++i) {
		c[i].c = read();
		c[i].id = i;
		v[i].emplace_back(-0x3f3f3f3f);
		for (int j = 1; j <= c[i].c; ++j) {
			int x;
			x = read();
			v[i].emplace_back(x);
		}
//		v[i].emplace_back(0x3f3f3f3f);
		sort(v[i].begin(), v[i].end());
	}
	
	sort(c + 1, c + 1 + n);
	
	int tot = 0;
	for (int i : v[c[1].id]) {
		a[++tot].maxn = i;
		a[tot].minn = i;
	}
	for (int i = 2; i <= n; ++i) {
		int id = c[i].id;
		for (int j = 1; j <= tot; ++j) {
			int l = lower_bound(v[id].begin(), v[id].end(), a[tot].minn) - v[id].begin() - 0;
			int r = upper_bound(v[id].begin(), v[id].end(), a[tot].maxn) - v[id].begin() - 1;
			if (r < l) {
//				if (r < 0) ++r;
//				cout << a[tot].minn << " " << a[tot].maxn << " " << v[id][l] << " " << v[id][r] << "\n";
				if (v[id][l] - a[tot].minn <= a[tot].maxn - v[id][r]) a[tot].maxn = max(a[tot].maxn, v[id][l]);
				else a[tot].minn = min(a[tot].minn, v[id][r]);
			}
		}
	}
	
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= tot; ++i) ans = min(ans, (long long)a[tot].maxn - a[tot].minn);
	printf("%lld", ans);
	
	return 0;
}
