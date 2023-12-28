#include <cstdio>
#include <algorithm>
#define N 100010
#define K 22
#define ll long long
using namespace std;
const int inf = 0x3f3f3f3f;
struct node
{
	bool type;
	int x, y;
} w;
int d1[N], d2[N], s1[N][K], s2[N][K], a[N];
int n, k, p[N], X, ans, f[N][K], f1[N][K], f2[N][K];
bool cmp(int a, int b) { return d1[a] > d1[b]; }
void work(int k)
{
	for (int i = 1; i <= n; i++)
		d1[i] = min(f1[i][k], f2[i][k]), d2[i] = min(f1[i][k + 1], f2[i][k + 1]), p[i] = i;
	sort(p + 1, p + n + 1, cmp);
	long long x;
	for (int i = 1, j = 2, d; j <= n; j++)
		if (d2[p[j]] > d2[p[i]])
		{
			x = 1ll * d1[p[j]] + d2[p[i]] + X, d = x - 2 * d1[p[j]];
			if (x < ans)
				ans = x, w = (node){1, k, d};
			i = j;
		}
}
inline int rd()
{
	register int a = 0, c = 0;
	while (c > '9' || c < '0')
		c = getchar();
	while (c >= '0' && c <= '9')
		a = (a << 3) + (a << 1) + (c ^ 48), c = getchar();
	return a;
}
int s[N];
ll _abs(int a) { return a > 0 ? a : -a; }
void check(int x, int y, ll val)
{
	if (s[x] > val)
		s[x] = val, a[x] = y;
}
int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	n = rd(), k = rd(), X = rd();
	ans = inf + inf;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
			f[i][j] = rd();
		f1[i][0] = f2[i][k + 1] = inf;
		for (int j = 1; j <= k; j++)
			f1[i][j] = min(f1[i][j - 1] + X, f[i][j]);
		for (int j = k; j; j--)
			f2[i][j] = min(f2[i][j + 1] + X, f[i][j]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			s1[i][j] = max(s1[i - 1][j], min(f1[i][j], f2[i][j]));
	for (int i = n; i; i--)
		for (int j = 1; j <= k; j++)
			s2[i][j] = max(s2[i + 1][j], min(f1[i][j], f2[i][j]));
	for (int i = 1; i <= n; i++)
		for (int j = 1, z; j <= k; j++)
		{
			z = max(s1[i - 1][j], s2[i + 1][j]);
			if (f[i][j] >= z && f[i][j] + z < ans)
				ans = f[i][j] + z, w = (node){0, i, j};
		}
	for (int i = 1; i <= k; i++)
		if (s1[n][k] * 2 < ans)
			ans = s1[n][k] * 2, w = (node){1, i, 0};
	for (int i = 1; i < k; i++)
		work(i);
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		s[i] = inf * 2;
	if (w.type == 0)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= k; j++)
				check(i, j, _abs(j - w.y) * X + f[i][j]);
		a[w.x] = w.y;
	}
	else
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= w.x; j++)
				check(i, j, 2ll * (w.x - j) * X + w.y + 2 * f[i][j]);
		for (int i = 1; i <= n; i++)
			for (int j = w.x + 1; j <= k; j++)
				check(i, j, 2ll * (j - w.x) * X - w.y + 2 * f[i][j]);
	}
	// for(int i=1;i<=n;i++) printf("%d ",a[i]);
}