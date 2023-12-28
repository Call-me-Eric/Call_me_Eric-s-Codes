#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXN(1000007);
int b[MAXN], c[MAXN];
char ch;
int n, m, tim;
struct matrix{
	int a[57][57];
	matrix() { memset(a, 0, sizeof(a)); }
	friend matrix operator * (matrix x, matrix y) {
		matrix z;
		for (int i(1); i <= 50; ++i)
			for (int j(1); j <= 50; ++j)
				for (int k(1); k <= 50; ++k)  z.a[i][j] ^= (x.a[i][k] & y.a[k][j]);
		return z;
	}
}a, base, ans;
inline void read(int &temp) { cin >> temp; }
inline void ksm(int k) {
	memset(ans.a, 0, sizeof(ans.a));
	for (int i(1); i <= n; ++i)  ans.a[i][i] = 1;
	while (k) {
		if (k & 1)  ans = ans * base;
		base = base * base, k >>= 1;
	}
}
inline void work() {
	read(tim);
	base = a;
	ksm(tim);
	for (int i(1); i <= n; ++i)
		for (int j(1); j <= n; ++j)  c[i] ^= (ans.a[i][j] & b[j]);
	for (int i(1); i <= n; ++i)  cout << c[i];
	cout << '\n';
	for (int i(1); i <= n; ++i)  c[i] = 0;
}
int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i(1); i <= n; ++i) {
		for (int j(1); j <= n; ++j) {
			cin >> ch;
			a.a[i][j] = ch - '0';
		}
	}
	for (int i(1); i <= n; ++i) {
		cin >> ch;
		b[i] = ch - '0';
	}
	read(m);
	while (m--)  work();
	return 0;
}
