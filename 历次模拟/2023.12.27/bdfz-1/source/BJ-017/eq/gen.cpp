#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 705;
const int P = 998244353;

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int n, q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	n = 700, q = 700;
	cout << n << " " << q << "\n";
	rep(i, 1, n) rep(j, 1, n+1) cout << mtrnd() % P << " \n"[j == n+1];
	while(q--) {
		int j = mtrnd() % n + 1;
		cout << j << " ";
		rep(i, 1, n+1) cout << mtrnd() % P << " \n"[i == n+1];
	}

	return 0;
}
