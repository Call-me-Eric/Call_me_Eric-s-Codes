#include <bits/stdc++.h>
#define ll long long
#define ls (k << 1)
#define rs (k << 1 | 1)
#define mid (l + r >> 1)
using namespace std;

const int N = 1e5 + 0721;
int a[N], loc[N];
vector<int> v[N];
int n, m;
ll ans[N];

struct tree {
	ll tr[N << 2];
	
	inline void pushup(int k) {
		tr[k] = tr[ls] + tr[rs];
	}
	
	void modify(int k, int l, int r, int loc, int val) {
		if (l == r) {
			tr[k] += val;
			return;
		}
		if (loc <= mid) modify(ls, l, mid, loc, val);
		else modify(rs, mid + 1, r, loc, val);
		pushup(k);
	}
	
	ll query(int k, int l, int r, int u, int v) {
		if (u <= l && v >= r) {
			return tr[k];
		}
		ll res = 0;
		if (u <= mid) res += query(ls, l, mid, u, v);
		if (v > mid) res += query(rs, mid + 1, r, u, v);
		return res;
	}
} seg;

struct node {
	int l, r, id;
	friend bool operator<(node x, node y) {
		return x.l > y.l;
	}
} q[N];

void init() {
	for (int i = 1; i <= n * 2; ++i) {
		int k = sqrt(i);
		if (k * k == i) v[0].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < v[0].size(); ++j) {
			int x = v[0][j];
			if (x - i <= 0) continue;
			v[i].push_back(x - i);
//			cout << i << " " << x - i << "\n";
		}
	}
} 

void solve() {
	int prs = 1;
	for (int i = n; i >= 1; --i) {
		for (int k = 0; k < v[a[i]].size(); ++k) {
			int j = v[a[i]][k];
			if (loc[j] > i) seg.modify(1, 1, n, loc[j], 1);
		}
		while (q[prs].l == i && prs <= m) {
			ans[q[prs].id] = seg.query(1, 1, n, q[prs].l, q[prs].r);
			++prs;
		}
	}
}

int main() {
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		loc[a[i]] = i;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	
	init();
	sort(q + 1, q + 1 + m);
	solve();
	
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	
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
