#include <iostream>
using namespace std;
int n, k, ans(-1), tim, cyc, yn;
inline void read(int &temp) { cin >> temp; }
int main() {
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(k);
	for (int i(2); i <= k; ++i) {
		if (n % i)  continue;
		int num = k - k % i;
		if (num > ans)  ans = num, tim = i, cyc = n / i, yn = k / i;
	}
	if (ans == -1) {
		for (int i(1); i <= n; ++i)  cout << "0";
		cout << endl;
		return 0;
	}
	for (int i(1); i <= tim; ++i) {
		for (int j(1); j <= yn; ++j)  cout << "1";
		for (int j(yn + 1); j <= cyc; ++j)  cout << "0";
	}
	cout << endl;
	return 0;
}
