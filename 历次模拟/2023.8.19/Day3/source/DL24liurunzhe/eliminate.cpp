# include <cstdio>
# include <vector>
# include <cctype>
# include <cassert>
# include <utility>
# include <algorithm>

class IO {
	static constexpr int MAXS = 1 << 20;
	
	char buf[MAXS], *p1 = buf, *p2 = buf;
	
	# define GetC() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXS, stdin), p1 == p2) ? EOF : *p1 ++)
	
 public:
	template <typename T> inline void read(T& x) {
		x = 0; bool f = 0; char ch = GetC();
		for (; !isdigit(ch); ch = GetC()) if (ch == '-') f = 1;
		for (; isdigit(ch); ch = GetC()) x = x * 10 + ch - '0';
		if (f) x = -x;
	}
	
	template <typename T, typename ...Args> inline void read(T& x, Args& ...rest) {
		read(x), read(rest...);
	}
} io;

using std::min;
using std::max;

typedef std::pair<int, int> Pii;

constexpr int MAXN = 1e6 + 5;

int n, num[MAXN << 1];

std::vector<int> vec[MAXN << 1];

int solve(int l, int r) {
	std::vector<Pii> arr; arr.reserve(n);
	for (int i = 1; i <= n; ++i) {
		if (vec[i].size() == 1) {
			l = min(l, *vec[i].begin());
			r = max(r, *vec[i].begin());
		} else
		if (*vec[i].begin() >= l) {
			r = max(r, *vec[i].begin());
		} else 
		if (*(vec[i].end() - 1) <= r) {
			l = min(l, *(vec[i].end() - 1));
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (vec[i].size() == 1) {
			l = min(l, *vec[i].begin());
			r = max(r, *vec[i].begin());
		} else
		if (*vec[i].begin() >= l) {
			r = max(r, *vec[i].begin());
		} else 
		if (*(vec[i].end() - 1) <= r) {
			l = min(l, *(vec[i].end() - 1));
		} else {
			auto x = std::lower_bound(vec[i].begin(), vec[i].end(), l);
			arr.emplace_back(*(x - 1), *x);
		}
	}
	std::sort(arr.begin(), arr.end());
	int res = 2e9;
	for (auto k : arr) {
		int a = k.first, b = k.second;
		if (a >= l) continue;
		res = min(res, r - a), r = max(r, b);
	}
	return min(r - l, res);
}

int main() {
	
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	
	io.read(n);
	for (int i = 1; i <= n; ++i) {
		io.read(num[i]); vec[i].reserve(num[i]);
		for (int j = 1; j <= num[i]; ++j) {
			int x; io.read(x); vec[i].push_back(x);
		}
		std::sort(vec[i].begin(), vec[i].end());
	}
	if (n == 1) return puts("0"), 0;
	int mn = 1e9, id = -1, mn2 = 1e9, id2 = -1;
	for (int i = 1; i <= n; ++i) {
		if (num[i] < mn) mn2 = mn, id2 = id, mn = num[i], id = i;
		else if (num[i] < mn2) mn2 = num[i], id2 = i;
	}
	int ans = 2e9;
	for (int k : vec[id]) {
		auto x = std::lower_bound(vec[id2].begin(), vec[id2].end(), k);
		if (x != vec[id2].end()) ans = min(ans, solve(k, *x));
		if (x != vec[id2].begin()) ans = min(ans, solve(*(x - 1), k));
	}
	printf("%d\n", ans);
	
	return 0;
}
