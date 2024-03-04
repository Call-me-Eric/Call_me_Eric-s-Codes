# include <cstdio>
# include <vector>
# include <map>
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
		x = 0; char ch = GetC();
		for (; !isdigit(ch); ch = GetC());
		for (; isdigit(ch); ch = GetC()) x = x * 10 + ch - '0';
	}
	
	template <typename T, typename ...Args> inline void read(T& x, Args& ...rest) {
		read(x), read(rest...);
	}
} io;

typedef long long LL;
typedef std::pair<LL, LL> Pii;

const int MAXN = 5e4 + 5;

int n, q;

LL a[MAXN << 1], b[MAXN << 1], c[MAXN << 1], d[MAXN << 1];

std::map<Pii, int> cnt;
std::map<Pii, std::vector<LL> > mp1, mp2;

int query(std::vector<LL>& vec, LL x) {
	return vec.end() - std::lower_bound(vec.begin(), vec.end(), x);
}

int main() {
	
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	
	io.read(n, q);
	for (int i = 1; i <= n; ++i) {
		io.read(a[i], b[i]);
	}
	std::vector<Pii> vec1, vec2;
	for (int i = 1; i <= n; ++i) {
		while (a[i] && b[i]) {
			if (b[i] > a[i]) mp1[Pii(a[i], b[i] % a[i])].push_back(b[i]), vec1.emplace_back(a[i], b[i] % a[i]);
			if (b[i] <= a[i]) mp2[Pii(b[i], a[i] % b[i])].push_back(a[i]), vec2.emplace_back(b[i], a[i] % b[i]);
			a[i] > b[i] ? a[i] %= b[i] : b[i] %= a[i]; ++cnt[Pii(a[i], b[i])];
		}
	}
	for (Pii k : vec1) {
		std::sort(mp1[k].begin(), mp1[k].end());
	}
	for (Pii k : vec2) {
		std::sort(mp2[k].begin(), mp2[k].end());
	}
	for (int i = 1; i <= q; ++i) {
		io.read(c[i], d[i]);
		printf("%d\n", query(mp1[Pii(c[i], d[i] % c[i])], d[i]) + query(mp2[Pii(d[i], c[i] % d[i])], c[i]) - cnt[Pii(c[i], d[i])]);
	}
	
	return 0;
}
