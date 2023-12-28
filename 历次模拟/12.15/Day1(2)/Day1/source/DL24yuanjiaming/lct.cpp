#include <iostream>
#include <vector>
using namespace std;
constexpr int MAXN(1000007);
vector <int> e[MAXN], f[MAXN];
int tr[MAXN], ans[MAXN];
int n, m;
struct node{ int l, r, id; }q[MAXN];
struct BIT{
	inline int lowbit(int x) { return x & -x; }
	inline void update(int x, int val) { for (int i(x); i <= n; i += lowbit(i))  tr[i] += val; }
	inline int query(int x) { int res(0);  for (int i(x); i; i -= lowbit(i))  res += tr[i];  return res; }
}Luka;
inline void read(int &temp) { cin >> temp; }
int main() {
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m);
	for (int i(1), u, v; i < n; ++i)  read(u), read(v), e[max(u, v)].push_back(min(u, v));
	for (int i(1); i <= m; ++i)  read(q[i].l), read(q[i].r), q[i].id = i, f[q[i].r].push_back(i);
	for (int i(1); i <= n; ++i) {
		for (auto x : e[i])  Luka.update(x, 1);
		for (auto x : f[i])  ans[q[x].id] = i - q[x].l + 1 - Luka.query(i) + Luka.query(q[x].l - 1);
	}
	for (int i(1); i <= m; ++i)  cout << ans[i] << endl;
	return 0;
}
