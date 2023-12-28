#include <iostream>
#include <bitset>
using namespace std;
constexpr int MAXN(100007);
bitset <17> bs[MAXN];
int a[17][MAXN], b[MAXN][107];
int opt[MAXN], x[MAXN], y[MAXN];
int n, k, q, cnt, tot, maxn;
inline void read(int &temp) { cin >> temp; }
namespace Subtask1{
void main() {
	for (int i(1); i <= k; ++i)
		for (int j(1); j <= n; ++j)  b[i][j] = a[i][j];
	cnt = k;
	for (int i(1); i <= q; ++i) {
		if (opt[i] == 1) {
			++cnt;
			for (int j(1); j <= n; ++j)  b[cnt][j] = max(b[x[i]][j], b[y[i]][j]);
		}
		if (opt[i] == 2) {
			++cnt;
			for (int j(1); j <= n; ++j)  b[cnt][j] = min(b[x[i]][j], b[y[i]][j]);
		}
		if (opt[i] == 3)  cout << b[x[i]][y[i]] << '\n';
	}
}}
namespace Subtask2{
void main() {
	for (int i(1); i <= k; ++i)  bs[i][i] = 1;
	cnt = k;
	for (int i(1); i <= q; ++i) {
		if (opt[i] == 1)  bs[++cnt] = (bs[x[i]] | bs[y[i]]);
		if (opt[i] == 3) {
			int res(0);
			for (int j(1); j <= k; ++j)  if (bs[x[i]][j])  res = max(res, a[j][y[i]]);
			cout << res << '\n';
		}
	}
}}
int main() {
	freopen("compose.in", "r", stdin);
	freopen("compose.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(k), read(q);
	for (int i(1); i <= k; ++i)
		for (int j(1); j <= n; ++j)  read(a[i][j]), maxn = max(maxn, a[i][j]);
	for (int i(1); i <= q; ++i)  read(opt[i]), read(x[i]), read(y[i]);
	for (int i(1); i <= q; ++i)  if (opt[i] == 2)  ++tot;
	if (!tot)  Subtask2::main();
	else  Subtask1::main();
	return 0;
}
