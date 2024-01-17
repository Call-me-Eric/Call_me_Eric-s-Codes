#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 2e5 + 5;
const long double eps = 1e-8;
const long double pi = acos(-1);

int n, m, k;
int a[N], b[N], ans;
vector<int> prm;

void dfs(int d) {
	if(d == n) {
		if(m > ans) ans = m, memcpy(b, a, sizeof a);
		return;
	}
	vector<int> pos;
	int p = 0;
	while(m + n/d <= k) {
		while(a[p]) ++p;
		assert(p < d);
		pos.push_back(p);
		for(int i = p; i < n; i += d) assert(a[i] == 0), a[i] = 1;
		m += n/d;
	}
	for(int p : prm) if((n/d) % p == 0) dfs(d*p);
	for(int p : pos) for(int i = p; i < n; i += d) a[i] = 0;
	m -= pos.size() * (n/d);
}

bool check() {
	long double sx = 0, sy = 0;
	rep(i, 0, n-1) if(a[i]) {
		long double theta = 2 * pi / n * i;
		sx += cos(theta);
		sy += sin(theta);
	}
	return fabs(sx) < eps && fabs(sy) < eps;
}

void dfss(int p) {
	if(p == n) {
		if(m > ans) {
			if(check()) ans = m, memcpy(b, a, sizeof a);
		}
		return;
	}
	a[p] = 1;
	if(m != k) {
		++m;
		dfss(p+1);
		--m;
	}
	a[p] = 0;
	dfss(p+1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);

	cin >> n >> k;
	if(n == k) {
		rep(i, 1, n) cout << 1; cout << "\n";
		return 0;
	}
	if(k <= 1) {
		rep(i, 1, n) cout << 0; cout << "\n";
		return 0;
	}
	if(n <= 20) {
		dfss(0);
		rep(i, 0, n-1) cout << b[i]; cout << "\n";
	} else {
		int n0 = n;
		for(int i = 2; i * i <= n; ++i) {
			if(n0 % i == 0) {
				prm.push_back(i);
				while(n0 % i == 0) n0 /= i;
			}
		}
		if(n0 != 1) prm.push_back(n0);
		dfs(1);
		rep(i, 0, n-1) cout << b[i];
		cout << "\n";
	}

	return 0;
}
