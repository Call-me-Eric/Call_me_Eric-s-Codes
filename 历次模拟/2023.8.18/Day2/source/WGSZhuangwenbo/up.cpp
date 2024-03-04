#include <cstdio>
#include <utility>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

#define int long long

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using pii = std::pair<int, int>;

int n, q;

std::map<pii, int> f;

signed main() {
	freopen("up.in", "r", stdin), freopen("up.out", "w", stdout);

	n = rd(), q = rd();
	for(int i = 1; i <= n; i++) {
		int a = rd(), b = rd();
		while(a > 0 && b > 0) {
			f[{a, b}]++;
			if(a > b) a -= b;
			else b -= a;
		}
		f[{a, b}]++;
	}
	for(int i = 1; i <= q; i++) {
		int a = rd(), b = rd();
		if(f.count({a, b})) printf("%lld\n", f[{a, b}]);
		else puts("0");
	}
	return 0;
}

