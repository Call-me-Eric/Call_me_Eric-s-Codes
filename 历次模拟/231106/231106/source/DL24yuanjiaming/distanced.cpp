#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
constexpr int MAXN(1007);
int v[MAXN];
int n, t, col, duan(1);
struct node{
	int x, v;
	friend bool operator < (node x, node y) { return x.x < y.x; }
}a[MAXN];
inline void read(int &temp) { cin >> temp; }
void dfs(int nw, int lp) {
	if (nw == n + 1)  return v[duan] = max(v[duan], col), void();
	if (lp != -1 && a[nw].x - lp > t)  ++duan;
	col += a[nw].v;
	dfs(nw + 1, a[nw].x);
	if (lp != -1 && a[nw].x - lp > t)  --duan;
	col -= a[nw].v;
	dfs(nw + 1, lp);
}
signed main() {
	freopen("distanced.in", "r", stdin);
	freopen("distanced.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(t);
	for (int i(1); i <= n; ++i)  read(a[i].x);
	for (int i(1); i <= n; ++i)  read(a[i].v);
	sort(a + 1, a + n + 1);
	dfs(1, -1);
	for (int i(1); i <= n; ++i)  v[i] = max(v[i], v[i - 1]);
	for (int i(1); i <= n; ++i)  cout << v[i] << " ";
	cout << endl;
	return 0;
}
