#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long 
using namespace std;
constexpr int MAXN(1000007);
inline void read(int &temp) { cin >> temp; }
int b[MAXN];
int n, m, cnt, xctb, yctb, ans;
struct node{
	int x, y;
	friend bool operator < (node x, node y) { return (x.x == y.x) ? (x.y > y.y) : (x.x < y.x); }
}a[MAXN];
struct SUF_BIT{
	int tr[MAXN];
	SUF_BIT(){ memset(tr, 0, sizeof(tr)); }
	inline int lowbit(int x) { return x & -x; }
	inline void update(int x, int val) { for (int i(x); i; i -= lowbit(i))  tr[i] += val; }
	inline int query(int x) { int res(0);  for (int i(x); i <= m; i += lowbit(i))  res += tr[i];  return res; }
}Luka;
signed main() {
	freopen("value.in", "r", stdin);
	freopen("value.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i(1); i <= n; ++i)  read(a[i].x), read(a[i].y), b[++cnt] = a[i].x, b[++cnt] = a[i].y;
	sort(a + 1, a + n + 1), sort(b + 1, b + cnt + 1), m = unique(b + 1, b + cnt + 1) - b - 1;
	for (int i(1); i <= n; ++i)  a[i].x = lower_bound(b + 1, b + m + 1, a[i].x) - b, a[i].y = lower_bound(b + 1, b + m + 1, a[i].y) - b;
	for (int i(1); i <= n; ++i) {
		xctb = (n - i + 1) * b[a[i].x], yctb = 0;
		if (n <= 3000)  for (int j = 1; j <= n; ++j)  yctb = max(Luka.query(a[j].y) * b[a[j].y], yctb);
		for (int j = max(i - 500, 1ll); j <= i; ++j)  yctb = max(Luka.query(a[j].y) * b[a[j].y], yctb);
		for (int j = max(i / 2 - 100, 1ll); j <= min(i / 2 + 100, i - 500); ++j)  yctb = max(Luka.query(a[j].y) * b[a[j].y], yctb);
		ans = max(ans, xctb + yctb), Luka.update(a[i].y, 1);
	}
	cout << ans << endl;
	return 0;
}
