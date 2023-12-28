#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN(707);
constexpr int mod(998244353);
int a[MAXN][MAXN], na[MAXN][MAXN], num[MAXN], b[MAXN], nb[MAXN];
int n, q, ans;
inline void read(int &temp) { cin >> temp; }
inline int ksm(int base, int k) {
	int res(1);
	while (k) {
		if (k & 1)  res = res * base % mod;
		base = base * base % mod, k >>= 1;
	}
	return res;
}
namespace Subtask1{
void main(){
	ans = b[1] * ksm(a[1][1], mod - 2) % mod;
	if (b[1] != 0 && a[1][1] == 0)  cout << "NO\n";
	else if (b[1] == 0 && a[1][1] == 0)  cout << "MANY\n";
	else cout << ans << '\n';
	for (int i(1); i <= q; ++i) {
		b[1] = nb[i], a[1][1] = na[i][1];
		ans = b[1] * ksm(a[1][1], mod - 2) % mod;
		if (b[1] != 0 && a[1][1] == 0)  cout << "NO\n";
		else if (b[1] == 0 && a[1][1] == 0)  cout << "MANY\n";
		else cout << ans << '\n';
	}
}}
signed main() {
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(q);
	for (int i(1); i <= n; ++i) {
		for (int j(1); j <= n; ++j)  read(a[i][j]);
		read(b[i]);
	}
	for (int i(1); i <= q; ++i) {
		read(num[i]);
		for (int j(1); j <= n; ++j)  read(na[i][j]);
		read(nb[i]);
	}
	if (n == 1)  Subtask1::main();
	return 0;
}
