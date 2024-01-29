#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
int fir[MAXN], s[MAXN], att[MAXN], p[MAXN];
int T, m, a, b, L, R, ans, xhj;
inline void read(int &temp) { cin >> temp; }
inline bool check(int l, int r) { return (p[r] - p[l - 1]) > ((r - l + 1) * 3ll); }
inline void work() {
	read(L), read(R);
	int len = R - L;
	L = L % xhj, R = L + len, ans = 0;
	for (int i(L); i <= R; ++i)
		for (int j(i); j <= R; ++j)  if (check(i, j))  ++ans;
	cout << ans << '\n';
}
signed main() {
	freopen("dark.in", "r", stdin);
	freopen("dark.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(m), read(T);
	s[1] = 134775813 % m, fir[s[1]] = 1, a = 1103515245 % m, b = 1013904223 % m;
	for (int i(2); i <= 500000; ++i) {
		s[i] = (a * s[i - 1] % m + b) % m;
		if (fir[s[i]] && !xhj)  xhj = i - fir[s[i]];
		if (!fir[s[i]])  fir[s[i]] = i;
	}
	for (int i(1); i <= 500000; ++i) {
		if (s[i] & 1)  att[i] = 4;
		else if (s[i] % 4 == 0)  att[i] = 1;
		else  att[i] = 3;
	}
	for (int i(1); i <= 500000; ++i)  p[i] = p[i - 1] + att[i];
	while (T--)  work();
	return 0;
}
