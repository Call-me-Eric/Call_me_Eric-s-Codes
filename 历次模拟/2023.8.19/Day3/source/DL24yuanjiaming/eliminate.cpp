#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int MAXN = 2000007;
constexpr int INF = 0x7f7f7f7f;
int b[MAXN], vis[MAXN];
int n, cnt, tot, head = 1, tp, ans = INF;
vector <int> v[MAXN];
vector <int> a[MAXN];
inline void read(int &temp) { cin >> temp; }
int main() {
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i = 1, num; i <= n; ++i) {
		read(num);
		for (int j = 1, t; j <= num; ++j)  read(t), v[i].push_back(t), b[++cnt] = t;
	}
	sort(b + 1, b + cnt + 1);
	tot = unique(b + 1, b + cnt + 1) - b - 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < v[i].size(); ++j)  v[i][j] = lower_bound(b + 1, b + tot + 1, v[i][j]) - b, a[v[i][j]].push_back(i);
	for (int tail = 1; tail <= tot; ++tail) {
		if (!a[tail].size())  continue;
		for (int j = 0; j < a[tail].size(); ++j) {
			if (!vis[a[tail][j]])  ++tp;
			++vis[a[tail][j]];
		}
		while (head <= tail) {
			bool flg = false;
			for (int j = 0; j < a[head].size(); ++j) {
				if (vis[a[head][j]] == 1) {
					a[head].erase(a[head].begin(), a[head].begin() + j);
					flg = true;
					break;
				}
				--vis[a[head][j]];
			}
			if (!flg)  ++head;
			else  break;
		}
		if (tp == n)  ans = min(ans, b[tail] - b[head]);
	}
	cout << ans << endl;
	return 0;
}
/*
4
9 -5 9 2 8 5 4 3 3 8
2 10 8
1 -7
3 1 6 10
*/
