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

const int N = 703, M = N << 1, mod = 998244353;

int n, q, a[N][N];

inline int qpow(int x, int y) {int res = 1; while (y) {if (y & 1) res = 1ll * res * x % mod; x = 1ll * x * x % mod;} return res;}

namespace Sub1
{
	inline void query()
	{
		if (a[1][1] == 0 && a[1][2] == 0) puts("Many");
		else if (a[1][1] == 0 && a[1][2] != 0) puts("No");
		else printf("%lld\n", 1ll * a[1][2] * qpow(a[1][1], mod - 2) % mod);
		return;
	}
	
	void solve()
	{
		query();
		while (q--)
		{
			int id = gi <int> ();
			rep(i, 1, n + 1) a[id][i] = gi <int> ();
			query();
		}
	}
} //namespace Sub1

int main()
{
	freopen("eq.in", "r", stdin); freopen("eq.out", "w", stdout);
	n = gi <int> (), q = gi <int> ();
	rep(i, 1, n) rep(j, 1, n + 1) a[i][j] = gi <int> ();
	if (n == 1) return Sub1 :: solve(), !!0;
	return !!0;
}
