#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 25;
const long double eps = 1e-8;
const long double pi = acos(-1);

int n, m, k;
int a[N], b[N], ans;

bool check() {
	long double sx = 0, sy = 0;
	rep(i, 0, n-1) if(a[i]) {
		long double theta = 2 * pi / n * i;
		sx += cos(theta);
		sy += sin(theta);
	}
	return fabs(sx) < eps && fabs(sy) < eps;
}

void dfs(int p) {
	if(p == n) {
		if(m > ans) {
			if(check()) ans = m, memcpy(b, a, sizeof a);
		}
		return;
	}
	a[p] = 1;
	if(m != k) {
		++m;
		dfs(p+1);
		--m;
	}
	a[p] = 0;
	dfs(p+1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> k;
	assert(n <= 20);
	dfs(0);
	cout << ans << "\n";
	rep(i, 0, n-1) cout << b[i]; cout << "\n";

	return 0;
}
