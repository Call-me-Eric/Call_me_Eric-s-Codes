#include <iostream>
#include <vector>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
constexpr int mod(998244353);
constexpr int mod1(1000000009);
constexpr int mod2(1000000007);
constexpr int mod3(917120411);
vector <int> w[MAXN], hs1[MAXN], hs2[MAXN];
string s[MAXN];
int d1[MAXN], d2[MAXN];
int num[MAXN], val[MAXN], pnum[MAXN], pval[MAXN], ed[MAXN];
int n, tot, ans, maxn;
inline void read(int &temp) { cin >> temp; }
inline int query1(int x, int l, int r) { return (hs1[x][r] - hs1[x][l - 1] * d1[r - l + 1] % mod1 + mod1) % mod1; }
inline int query2(int x, int l, int r) { return (hs2[x][r] - hs2[x][l - 1] * d2[r - l + 1] % mod2 + mod2) % mod2; }
inline int calc(int x, int y) {
	int lx = (int)s[x].length(), ly = (int)s[y].length(), len = min(lx, ly);
	for (int i(len); i; --i) {
		int hsx1 = query1(x, lx - i + 1, lx), hsx2 = query2(x, lx - i + 1, lx);
		if (hsx1 == hs1[y][i] && hsx2 == hs2[y][i])  return (w[x][i] + w[y][i]) % mod;
	}
	return 0;
}
namespace Subtask2{
void main() {
	d1[0] = d2[0] = 1;
	for (int i(1); i <= tot; ++i)  d1[i] = d1[i - 1] * mod3 % mod1, d2[i] = d2[i - 1] * mod3 % mod2;
	for (int i(1); i <= n; ++i) {
		hs1[i].push_back(0), hs2[i].push_back(0);
		for (int j(1); j <= (int)(s[i].length()); ++j)  hs1[i].push_back((hs1[i][j - 1] * mod3 + (int)(s[i][j - 1] - 'a' + 1)) % mod1);
		for (int j(1); j <= (int)(s[i].length()); ++j)  hs2[i].push_back((hs2[i][j - 1] * mod3 + (int)(s[i][j - 1] - 'a' + 1)) % mod2);
	}
	for (int i(1); i <= n; ++i)
		for (int j(1); j <= n; ++j)  if (i != j)  ans = (ans + calc(i, j)) % mod;
	for (int i(1); i <= n - 1; ++i)  ans = ans * i % mod;
	cout << ans << endl;
}
}
namespace Subtask5{
void main() {
	for (int i(1); i <= tot; ++i)  pval[i] = (pval[i - 1] + ed[i]) % mod, pnum[i] = (pnum[i - 1] + val[i]) % mod;
	for (int i(1); i <= n; ++i) {
		int len = (int)s[i].length();
		int chang = (val[len] - w[i][len] + mod) % mod;
		int duan = pval[len - 1];
		ans = (ans + chang + duan) % mod;
	}
	ans = ans * 2 % mod;
	for (int i(1); i <= n - 1; ++i)  ans = ans * i % mod;
	cout << ans << endl;
}
}
signed main() {
	freopen("unpredictable.in", "r", stdin);
	freopen("unpredictable.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i(1); i <= n; ++i) {
		cin >> s[i];
		w[i].push_back(0), tot += s[i].length(), maxn = max(maxn, (int)s[i].length());
		for (int j(1), x; j <= (int)(s[i].length()); ++j)  read(x), w[i].push_back(x), val[j] = (val[j] + x) % mod;
		++num[s[i].length()], ed[s[i].length()] = (ed[s[i].length()] + w[i][s[i].length()]) % mod;
	}
	if (n <= 2000 && tot <= 100000)  Subtask2::main();
	else  Subtask5::main();
	return 0;
}
