#include <bits/stdc++.h>
using namespace std;
int read()
{
    int sum = 0, ne = 1;
    char ch = getchar();
    for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
    if (ch == '-')
        ne = -1, ch = getchar();
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        sum = (sum << 3) + (sum << 1) + (ch ^ 48);
    return sum * ne;
}
const int maxn = 15;
int fa[maxn];
tuple<int, int, char> tp[maxn * maxn];
int r, g, b, m, n, flag[maxn * maxn];
int fd(int x)
{
    return fa[x] != x ? fa[x] = fd(fa[x]) : x;
}
void dfs(int now, int r, int g, int b, int sum)
{
    if (sum == n - 1)
    {
        for (int i = 1; i <= n; i++) fa[i] = i;
        for (int i = 1; i <= now; i++)
            if (flag[i])
            {
                int x = fd(get<0>(tp[i])), y = fd(get<1>(tp[i]));
                if (x == y)
                    return;
                fa[x] = y;
            }
        puts("YES");
        for (int i = 1; i <= m; i++)
            printf("%d ", flag[i]);
        exit(0);
    }
    if (now > m) return;
    char tmp = get<2>(tp[now]);
    if (tmp == 'r')
    {
        dfs(now + 1, r, g, b, sum);
        if (r) 
        {
            flag[now] = 1;
            dfs(now + 1, r - 1, g, b, sum + 1);
            flag[now] = 0;
        }
    }
    else if (tmp == 'g')
    {
        dfs(now + 1, r, g, b, sum);
        if (g)
        {
            flag[now] = 1;
            dfs(now + 1, r, g - 1, b, sum + 1);
            flag[now] = 0;
        }
    }
    else
    {
        dfs(now + 1, r, g, b, sum);
        if (b) 
        {
            flag[now] = 1;
            dfs(now + 1, r, g, b - 1, sum + 1);
            flag[now] = 0;
        }
    }
}
int main()
{
    freopen("rgb.in", "r", stdin);
    freopen("rgb.out", "w", stdout);
    r = read(), g = read(), b = read(), m = read();
    n = r + g + b + 1;
    if (n <= 5)
    {
        for (int i = 1; i <= m; i++)
        {
            int x = read(), y = read();
            char c;
            cin >> c;
            tp[i] = make_tuple(x, y, c);
        }
        dfs(1, r, g, b, 0);
        puts("NO");
    }
    else puts("NO");
	return 0;
}
