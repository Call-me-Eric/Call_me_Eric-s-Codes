#include <bits/stdc++.h>
using namespace std;
namespace Solution
{
#ifdef LOCAL
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif
	typedef long long LL;
	const int N = 1e5 + 5;
	const LL INF = 1e18;
	int n;
	LL a[N];
	struct Edge
	{
		int v;
		LL w;
		Edge() : v(0), w(0) {}
		Edge(int v_ = 0, LL w_ = 0) : v(v_), w(w_) {}
	};
	vector<Edge> tree[N];
	void adde(int u, int v, LL w) { tree[u].push_back(Edge(v, w)), tree[v].push_back(Edge(u, w)); }
	bool vis[N];
	int sum, si[N], rt, mx;
	void find(int u, int fa)
	{
		si[u] = 1;
		int res = 0;
		for (Edge e : tree[u])
			if (!vis[e.v] && e.v != fa)
				find(e.v, u), si[u] += si[e.v], res = max(res, si[e.v]);
		res = max(res, sum - si[u]);
		if (res < mx)
			rt = u, mx = res;
	}
	int tot;
	LL need[N], last[N];
	void dfs(int u, int fa, int fi, LL w, LL rest, LL mn)
	{
		++tot;
		need[tot] = need[fi] + max(w - rest, 0LL), rest = max(rest - w, 0LL) + a[u];
		mn = min(a[u] - w, mn + a[u] - w), last[tot] = last[fi] + a[u] - w;
		fi = tot;
		for (Edge e : tree[u])
			if (!vis[e.v] && e.v != fa)
				dfs(e.v, u, fi, e.w, rest, mn);
		mn < 0 ? last[fi] = -INF : 0;
	}
	LL ans;
	LL solve(int l, int r)
	{
		int pn = l;
		LL res = 0;
		sort(need + l, need + r + 1), sort(last + l, last + r + 1);
		for (int i = l; i <= r; ++i)
		{
			while (pn <= r && need[pn] <= last[i] + a[rt])
				++pn;
			res += pn - l;
		}
		return res;
	}
	void solve()
	{
		tot = 0;
		for (Edge e : tree[rt])
			if (!vis[e.v])
			{
				int l = tot + 1, r;
				dfs(e.v, rt, 0, e.w, 0, 0), r = tot;
				ans -= solve(l, r);
			}
		ans += solve(1, tot);
		for (int i = 1; i <= tot; ++i)
			ans += int(last[i] >= 0) + int(need[i] <= a[rt]);
	}
	void dfz(int u)
	{
		solve(), vis[u] = true;
		for (Edge e : tree[u])
			if (!vis[e.v])
				sum = si[e.v], rt = 0, mx = n, find(e.v, u), find(rt, 0), dfz(rt);
	}
	int main()
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%lld", &a[i]);
		for (int i = 1; i <= n - 1; ++i)
		{
			int u, v;
			LL w;
			scanf("%d %d %lld", &u, &v, &w), adde(u, v, w);
		}
		sum = n, rt = 0, mx = n, find(1, 0), find(rt, 0), dfz(rt);
		printf("%lld\n", ans);
		return 0;
	}
}
int main()
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
	Solution::main();
	return 0;
}