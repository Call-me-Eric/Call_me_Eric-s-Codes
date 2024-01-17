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
	T x = 0, f = 0; char c = getchar();
	while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return f ? -x : x;
}

const int N = 100003;

bool ok[N];
int s[N], cnt;
int sum[N];

inline bool pri(int o)
{
	if (o <= 1) return 0;
	rep(i, 2, o - 1) if (o % i == 0) return 0;
	return 1;
}

inline bool check(int u, bool fl = 0)
{
	cnt = 0;
	while (u) s[++cnt] = u % 10, u /= 10;
	reverse(s + 1, s + 1 + cnt);
	rep(i, 1, (1 << cnt) - 1)
	{
		int now = 0;
		rep(j, 1, cnt) if (i >> (j - 1) & 1) now = now * 10 + s[j];
		if (pri(now))
		{
			if (fl) cout << now << endl;
			return 0;
		}
	}
	return 1;
}

int main()
{
	freopen("prime.in", "r", stdin); freopen("prime.ans", "w", stdout);
	rep(i, 1, 100000) ok[i] = check(i), sum[i] = sum[i - 1] + ok[i];
	int T = gi <int> (); while (T--) {int l = gi <int> (), r = gi <int> (); cout << sum[r] - sum[l - 1] << endl;}
	return !!0;
}
