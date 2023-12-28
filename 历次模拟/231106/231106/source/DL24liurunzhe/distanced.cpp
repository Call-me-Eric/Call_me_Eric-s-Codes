# include <cstdio>
# include <vector>
# include <algorithm>

# define int long long

int n, d;

namespace Sub1 {
	constexpr int MAXN = 1e5 + 5;
	
	struct Str {
		int x, val;
	} str[MAXN << 1];
	
	int fa[MAXN << 1], sum[MAXN << 1];
	
	int find(int x) {
		return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
	}
	
	void unite(int x, int y) {
		sum[find(y)] += sum[find(x)];
		fa[find(x)] = find(y);
	}
	
	void main() {
		for (int i = 1; i <= n; ++i) scanf("%lld", &str[i].x);
		for (int i = 1; i <= n; ++i) scanf("%lld", &str[i].val);
		std::sort(str + 1, str + n + 1, [&](const Str& A, const Str& B) {
			return A.x < B.x;
		});
		for (int i = 1; i <= n; ++i) fa[i] = i, sum[i] = str[i].val;
		for (int i = 2; i <= n; ++i) {
			if (str[i].x - str[i - 1].x <= d) unite(i, i - 1);
		}
		std::vector<int> vec;
		for (int i = 1; i <= n; ++i) if (fa[i] == i) {
			vec.push_back(sum[i]);
		}
		std::sort(vec.begin(), vec.end());
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vec.empty()) ans += vec.back(), vec.pop_back();
			printf("%lld%c", ans, " \n"[i == n]);
		}
	}
}

constexpr int MAXN = 2e3 + 5;

int trans[MAXN];

int f[MAXN][MAXN], pre[MAXN][MAXN];

int que[MAXN << 1], *hd, *tl;

struct Str {
	int x, val;
} str[MAXN << 1];

signed main() {
	
	freopen("distanced.in", "r", stdin);
	freopen("distanced.out", "w", stdout);
	
	scanf("%lld %lld", &n, &d);
	if (n > 2000) return Sub1::main(), 0;
	for (int i = 1; i <= n; ++i) scanf("%lld", &str[i].x);
	for (int i = 1; i <= n; ++i) scanf("%lld", &str[i].val);
	std::sort(str + 1, str + n + 1, [&](const Str& A, const Str& B) {
		return A.x < B.x;
	});
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) 
			if (str[i].x - str[j].x <= d) { trans[i] = j; break; }
	}
	f[1][1] = str[1].val;
	for (int k = 1; k <= n; ++k) {
		hd = tl = que;
		for (int i = 1; i <= n; ++i) {
			f[i][k] = pre[ trans[i] - 1 ][k - 1] + str[i].val;
			while (tl - hd > 0 && *hd < trans[i]) hd ++;
			if (tl - hd > 0) f[i][k] = std::max(f[i][k], f[*hd][k] + str[i].val);
			while (tl - hd > 0 && f[i][k] >= f[*(tl - 1)][k]) tl --; *tl ++ = i;
			pre[i][k] = std::max(pre[i - 1][k], f[i][k]);
		}
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) f[n][k] = std::max(f[n][k], f[i][k]);
		printf("%lld%c", f[n][k] = std::max(f[n][k], f[n][k - 1]), " \n"[k == n]);
	}
	
	return 0;
}
