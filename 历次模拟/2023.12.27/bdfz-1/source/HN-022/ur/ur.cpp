#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i+=1)
#define per(i, x, y) for (int i = (x); i >= (y); i-=1)
#define epr(i, x) for (int i = head[x]; i; i = nxt[i])
#define fi first
#define se second
#define ep emplace
#define eb emplace_back

using namespace std;

typedef long long LL;
typedef pair <int, int> PII;

template <typename T>
inline T gi()
{
    T x = 0; bool f = 0; char c = getchar();
    while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return f ? -x : x;
}

const int N = 1000003, M = N << 1;
const double pi = acos(-1);

int n, k;
vector <PII> fac;

inline bool isprime(int x)
{
	for (int i = 2; i * i <= x; i+=1) if (x % i == 0) return 0;
	return 1;
}

namespace Sub1
{
	int ans, res;
	
	void solve()
	{
		double o = (pi + pi) / n;
		rep(s, 1, (1 << n) - 1)
		{
			int cnt = __builtin_popcount(s);
			if (cnt <= ans || cnt > k) continue;
			double x = 0, y = 0;
			rep(i, 0, n - 1) if (s >> i & 1) x += cos(o * i), y += sin(o * i);
			if (fabs(x) < 1e-8 && fabs(y) < 1e-8) ans = __builtin_popcount(s), res = s;
		}
		rep(i, 0, n - 1) printf("%d", res >> i & 1);
		return;
	}
} //namespace Sub1

int main()
{
	freopen("ur.in", "r", stdin); freopen("ur.out", "w", stdout);
	n = gi <int> (), k = gi <int> ();
	if (k == n) {printf("%d\n", n); rep(i, 1, n) putchar('1'); return !!0;}
	if (k <= 1 || isprime(n)) {puts("0"); rep(i, 1, n) putchar('0'); return !!0;}
	if (n <= 20) return Sub1 :: solve(), !!0;
	int ans = 0, o = 0;
	rep(i, 2, k) if (n % i == 0 && (k / i) * i > ans) ans = (k / i) * i, o = i;
	rep(i, 0, n - 1) if (i % (n / o) < k / o) putchar('1'); else putchar('0');
	return !!0;
}
