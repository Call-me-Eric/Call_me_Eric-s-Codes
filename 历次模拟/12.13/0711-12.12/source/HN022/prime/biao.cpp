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

vector <int> vec;

inline bool check(int u) {if (u <= 1) return 0; rep(i, 2, u - 1) if (u % i == 0) return 0; return 1;}

void dfs(int u, int o, bool fl)
{
	if (o > 7) return;
	if (o == 7 && check(u)) vec.eb(u);
	if (o != 1) dfs(u * 10 + 0, o + 1, fl);
//	dfs(u * 10 + 1, o + 1, fl);
	dfs(u * 10 + 4, o + 1, fl);
	dfs(u * 10 + 6, o + 1, fl);
	if (!fl) dfs(u * 10 + 8, o + 1, fl);
	dfs(u * 10 + 9, o + 1, 1);
}

int main()
{
	//freopen("prime.in", "r", stdin); freopen("prime.out", "w", stdout);
	dfs(0, 1, 0);
	sort(begin(vec), end(vec)); vec.erase(unique(begin(vec), end(vec)), end(vec));
	for (auto x : vec) cout << x << endl;
	return !!0;
}
