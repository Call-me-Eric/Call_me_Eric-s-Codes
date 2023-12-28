#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 45;
const int P = 998244353;

int n, m, q, k;
int a[N], b[N];
map<vector<int>, int> f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	cin >> m;
	rep(i, 1, m) cin >> b[i];
	cin >> q >> k;
	assert(q == 1);
	f[0][vector<int>(a + 1, a + 35)] = 1;
	rep(i, 1, k) {
		for(auto e : f[i-1]) {
			const auto v = e.fi;
			const int val = e.se;
			for(int j = 0; j < 31; ++j) {
				if(j == 0 || v[j-1] > v[j]) {
					auto w = v; ++w[j];
					f[i][w] = (f[i][w] + val) % P;
				}
				if(v[j] > v[j+1]) {
					auto w = v; --w[j];
					f[i][w] = (f[i][w] + val) % P;
				}
			}
		}
	}
	cout << f[k][vector<int>(b + 1, b + 35)] << "\n";

	return 0;
}
