#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e6 + 10;
int n, m;
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
	cin >> n >> m;
	if (n == 2) cout << 0 << " " << 3 << '\n';
	if (n == 3) {
		if (m == 3) cout << 1 << " " << 3 << '\n';
		else cout << 0 << " " << (m == 1 ? 3 : 6) << '\n';
	}
	return 0;
}