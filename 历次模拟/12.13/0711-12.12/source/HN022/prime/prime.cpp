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

const int N = 200003, mod = 998244353;

string s;
int lim, l[N];
int su[N], pw[N], pw3[N], pw2[N], su2[N];
int val[10], val1[10];
int ans;
bool ok[N];
int ss[N], cnt;
int sum[N];

int dfs1(int u, int tar)
{
	if (u > tar) return 1;
	if (l[u] == 4 || l[u] == 6 || l[u] == 8 || l[u] == 0) return (1ll * val[l[u]] * pw[tar - u] % mod + dfs1(u + 1, tar)) % mod;
	return 1ll * val[l[u]] * pw[tar - u] % mod;
}

int dfs2(int u, int tar)
{
	if (u > tar) return 1;
	if (l[u] == 9 || l[u] == 6 || l[u] == 0) return (1ll * val1[l[u]] * pw3[tar - u] % mod + dfs2(u + 1, tar)) % mod;
	return 1ll * val1[l[u]] * pw3[tar - u] % mod;
}

int dfs3(int u, int tar)
{
	if (u > tar) return 1;
	if (l[u] == 6 || l[u] == 0) return (1ll * ((l[u] > 0) + (l[u] > 6)) * pw2[tar - u] % mod + dfs3(u + 1, tar)) % mod;
	return 1ll * ((l[u] > 0) + (l[u] > 6)) * pw2[tar - u] % mod;
}

inline void solve1(string o)
{
	int len = o.size();
	if (len < 2) return;
	rep(i, 2, len - 1) (ans += su[i - 2]) %= mod;
	if (l[0] < 4) return;
	bool fl = l[0] > 4;
	rep(i, 1, len - 1)
	{
		if (fl || l[i] == 9)
		{
			if (fl) (ans += pw[len - 1 - i]) %= mod;
			else (ans += dfs1(i + 1, lim - 1)) %= mod;
		}
		if (!fl && l[i] < 6) return;
		fl |= (l[i] > 6);
	}
}

inline void solve2(string o)
{
	int len = o.size();
	rep(i, 1, len - 1)
	{
		(ans += 1ll * (pw[i - 1] + mod - pw2[i - 1]) % mod) %= mod;
		rep(j, 2, i) (ans += 1ll * 2 * pw3[j - 2] % mod * (pw[i - j] + mod - pw2[i - j]) % mod) %= mod;
//		cout << i << ' ' << ans << endl;
	}
	if (l[0] < 6) return;
//	cout << ans << endl;
	rep(i, 0, len - 2) //9's position
	{
		int cnt = 0;
		bool ok = 1;
		rep(j, 0, i - 1)
		{
			(cnt += 1ll * ((j > 0 && l[j] > 0) + (l[j] > 6)) * pw3[i - 1 - j] % mod) %= mod;
			if (l[j] != 0 && l[j] != 6 && l[j] != 9) {ok = 0; break;}
		}
		int dlt = ans;
		if (ok && l[i] == 9) (ans += (dfs1(i + 1, lim - 1) - dfs3(i + 1, lim - 1) + mod) % mod) %= mod;//, cout << dfs1(i + 1, lim - 1) << ' ' << dfs3(i + 1, lim - 1) << '!' << endl;
		(ans += 1ll * cnt * (pw[len - 1 - i] + mod - pw2[len - 1 - i]) % mod) %= mod;
//		cout << i << ' ' << ans - dlt << endl;
	}
}

inline void solve3(string o)
{
	int len = o.size();
	if (len < 2) return;
	rep(i, 2, len - 1) (ans += su[i - 2]) %= mod;
	if (l[0] < 8) return;
	bool fl = l[0] > 8;
	rep(i, 1, len - 1)
	{
		if (fl || l[i] >= 1)
		{
			if (fl || l[i] > 1) (ans += pw[len - 1 - i]) %= mod;
			else (ans += dfs1(i + 1, lim - 1)) %= mod;
		}
		fl |= (l[i] > 0);
	}
}

inline void solve4(string o)
{
	int len = o.size();
	if (len < 3) return;
	rep(i, 2, len - 1) (ans += su[i - 3]) %= mod;
	if (l[0] < 9 || l[1] < 8) return;
	bool fl = l[1] > 8;
	rep(i, 2, len - 1)
	{
		if (fl || l[i] >= 1)
		{
			if (fl || l[i] > 1) (ans += pw[len - 1 - i]) %= mod;
			else (ans += dfs1(i + 1, lim - 1)) %= mod;
		}
		fl |= (l[i] > 0);
	}
}

inline void solve(string o, string x)
{
	int sx = x.size(), so = o.size();
	if (so < sx) return;
	rep(i, sx, so - 1) (ans += pw[i - sx]) %= mod;
	bool fl = 0;
	rep(i, 0, sx - 1) if (o[i] < x[i]) return; else if (o[i] > x[i]) {fl = 1; break;}
//	cout << fl << endl;
	if (fl) {(ans += pw[so - sx]) %= mod; return;}
	(ans += dfs1(sx, so - 1)) %= mod;
}

inline int solve(string o)
{
	if (o == "0") return 1;
	lim = o.size();
	rep(i, 0, lim - 1) l[i] = o[i] - '0';
	int res1 = dfs1(0, lim - 1), res2 = dfs2(0, lim - 1), res3 = dfs3(0, lim - 1);
//	cout << o << ":::\n";
//	cout << res1 << ' ' << res2 << ' ' << res3 << endl;
	ans = (1ll * res1 + res2 + mod - res3) % mod;
//	cout << ans << endl;
	solve1(o); //466...69
//	cout << "466...69 " << ans << endl;
	solve2(o); //6(0/6)(0/6)...(0/6)9
//	cout << "666...69 " << ans << endl;
	solve3(o); //800...01
//	cout << "800...01 " << ans << endl;
//	solve4(o); //9800...01
//	cout << "9800...01 " << ans << endl;
	solve(o, "9801");
	solve(o, "981");
	solve(o, "9081");
	solve(o, "6049");
	solve(o, "60049");
	solve(o, "600049");
	solve(o, "6000049");
	solve(o, "6409");
	solve(o, "64009");
//	cout << "6609 " << ans << endl;
	solve(o, "649");
	solve(o, "6649");
	solve(o, "66649");
//	cout << "6649 " << ans << endl;
	solve(o, "949");
	solve(o, "9469"); 
//	cout << "9469 " << ans << endl;
	solve(o, "94669"); 
//	cout << "94669 " << ans << endl;
	solve(o, "901"); 
//	cout << "901 " << ans << endl;
	solve(o, "91"); 
//	cout << "91 " << ans << endl;
	solve(o, "1");
//	cout << "1 " << ans << '!' << endl;
	return ans;
}

int pp;

inline void solve()
{
	cin >> s;
	int len = s.size();
	bool fl = 1;
	if (len > 5) fl = 0;
	pp = 0; rep(i, 0, len - 1) pp = pp * 10 + s[i] - '0';
	int ol = sum[pp];
	per(i, len - 1, 0) if (s[i] == '0') s[i] = '9'; else {--s[i]; break;}
	int res = solve(s);
	cin >> s; len = s.size();
	if (len > 5) fl = 0;
	pp = 0; rep(i, 0, len - 1) pp = pp * 10 + s[i] - '0';
	if (fl) return (void)printf("%d\n", sum[pp] - ol);
	printf("%d\n", (solve(s) + mod - res) % mod);
	return;
}

inline bool pri(int o)
{
	if (o <= 1) return 0;
	rep(i, 2, o - 1) if (o % i == 0) return 0;
	return 1;
}

inline bool check(int u)
{
	cnt = 0;
	while (u) ss[++cnt] = u % 10, u /= 10;
	reverse(ss + 1, ss + 1 + cnt);
	rep(i, 1, (1 << cnt) - 1)
	{
		int now = 0;
		rep(j, 1, cnt) if (i >> (j - 1) & 1) now = now * 10 + ss[j];
		if (pri(now))
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	freopen("prime.in", "r", stdin); freopen("prime.out", "w", stdout);
	rep(i, 1, 100000) ok[i] = check(i), sum[i] = sum[i - 1] + ok[i];
	rep(i, pw[0] = pw3[0] = pw2[0] = 1, 200000) pw[i] = 4ll * pw[i - 1] % mod, pw3[i] = 3ll * pw3[i - 1] % mod, pw2[i] = 2ll * pw2[i - 1] % mod;
	rep(i, su[0] = su2[0] = 1, 200000) su[i] = (su[i - 1] + pw[i]) % mod, su2[i] = (su2[i - 1] + pw2[i]) % mod;
	val[0] = 0, val[1] = val[2] = val[3] = val[4] = 1, val[5] = val[6] = 2, val[7] = val[8] = 3, val[9] = 4;
	val1[0] = 0, val1[1] = val1[2] = val1[3] = val1[4] = val1[5] = val1[6] = 1, val1[7] = val1[8] = val1[9] = 2;
	int T = gi <int> (); while (T--) solve();
	return !!0;
}
