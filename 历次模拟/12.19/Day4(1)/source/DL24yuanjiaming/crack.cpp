#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
constexpr int mod(1000000007);
int f[MAXN], a[MAXN], ans[MAXN];
int t, n, m;
inline void read(int &temp) { cin >> temp; }
inline int ksm(int base, int k) {
	int res(1);
	while (k) {
		if (k & 1)  res = (res * base % mod + mod) % mod;
		base = (base * base % mod + mod) % mod, k >>= 1;
	}
	return res;
}
namespace Subtask1{
void main() {
	read(n);
	if (n <= 2)  return cout << "12" << endl, void();
	int tim = 1;
	n -= 2;
	if (n % 2 == 0)  cout << (ksm(3, n + 1) % mod + 1ll + mod) % mod * ksm(4, mod - 2) % mod * tim % mod * 12ll % mod << endl;
	else  cout << (ksm(3, n + 1) % mod - 1ll + mod) % mod * ksm(4, mod - 2) % mod * tim % mod * 12ll % mod << endl;
}
}
namespace Subtask3{
void main() {
	read(n), read(m);
	for (int i(1); i <= n; ++i)  read(a[i]), f[i] = f[i - 1] + a[i];
	for (int i(1), u, v; i <= m; ++i) {
		read(u), read(v);
		ans[i] = f[v] - f[u - 1];
	}
	for (int i(1); i <= m; ++i)  cout << ans[i] << '\n';
}
}
signed main() {
	freopen("crack.in", "r", stdin);
	freopen("crack.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(t);
	if (t == 1)  Subtask1::main();
	if (t == 3)  Subtask3::main();
	return 0;
}
