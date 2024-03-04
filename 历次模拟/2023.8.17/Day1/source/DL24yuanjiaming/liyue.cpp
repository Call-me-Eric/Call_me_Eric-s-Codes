#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 10000007;
struct node{
	int l, r, opt;
	friend bool operator < (node x, node y) { return x.r < y.r; }
}s[MAXN], q[MAXN];
int a[MAXN], fd[MAXN], l[MAXN], r[MAXN], ans[MAXN], tr[MAXN];
int n, cnt, m, tot, now = 1;
struct Seg_Tree{
	#define ls (p << 1)
	#define rs (p << 1 | 1)
	#define mid ((l + r) >> 1)
	inline void pushup(int p) { tr[p] = tr[ls] + tr[rs]; }
	void update(int p, int l, int r, int x, int val) {
		if (l == r)  return tr[p] = tr[p] + val, void();
		if (x <= mid)  update(ls, l, mid, x, val);
		else  update(rs, mid + 1, r, x, val);
		pushup(p);
	}
	int query(int p, int l, int r, int x) {
		if (l == r)  return tr[p];
		int res = 0;
		if (x <= mid)  return tr[rs] + query(ls, l, mid, x);
		else  return query(rs, mid + 1, r, x);
	}
}Miku;
inline void read(int &temp) { cin >> temp; }
int main() {
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i = 1; i <= n; ++i)  read(a[i]), fd[a[i]] = i;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j * j <= (n << 1); ++j)  if (j * j - a[i] <= n && j * j - a[i] >= 1 && fd[j * j - a[i]] < i)  s[++cnt].l = fd[j * j - a[i]], s[cnt].r = i, s[cnt].opt = -1;
	read(m);
	for (int i = 1; i <= m; ++i)  read(q[++tot].l), read(q[tot].r), q[tot].opt = i;
	sort(q + 1, q + tot + 1);
	for (int i = 1; i <= cnt; ++i) {
		while (s[i].r > q[now].r && now <= tot)  ans[q[now].opt] = Miku.query(1, 1, n, q[now].l), ++now;
		if (now == tot)  break;
		Miku.update(1, 1, n, s[i].l, 1);
	}
	for (int i = now; i <= tot; ++i)  ans[q[i].opt] = Miku.query(1, 1, n, q[i].l);
	for (int i = 1; i <= m; ++i)  cout << ans[i] << endl;
	return 0;
}
/*
8
5 7 4 1 8 6 2 3
10
4 5
2 6
1 8
2 7
4 8
3 8
4 7
1 5
2 5
3 7

*/
