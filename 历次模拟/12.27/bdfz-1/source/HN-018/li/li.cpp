#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x first
#define y second
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1000010;

int n, m, cnt, ans0, ans1, ans2, vis[N], sum[N], head[N];

struct edge
{
    int to, nxt;
} e[N * 2];

inline void add(int x, int y)
{
    e[++cnt] = {y, head[x]}, head[x] = cnt;
    e[++cnt] = {x, head[y]}, head[y] = cnt;
}

inline void dfs(int now, int fa, int &dian, int &bian, int &du)
{
    dian++, vis[now] = 1; int x = 0;
    for(int i = head[now];i;i = e[i].nxt)    
        x++;
    du = max(du, x);
    for(int i = head[now];i;i = e[i].nxt)
    {
        if(e[i].to == fa) continue;
        bian++;
        if(!vis[e[i].to]) dfs(e[i].to, now, dian, bian, du);
    }
}

signed main()
{
	freopen("li.in", "r", stdin);
	freopen("li.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    fro(i, 1, N / 3)
        sum[i] = sum[i - 1] + i;
    fro(i, 1, m)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }
    fro(i, 1, n)
        if(!vis[i])
        {
            int d = 0, b = 0, u = 0;
            dfs(i, 0, d, b, u);
            if(u <= 2)
            {
                if(d == b + 1)
                    ans2 += sum[d];
                else ans1 += d;
            }
            else if(d == 4 && b == 3 && u == 3)
                ans1 += 3;
            else ans0 = 1;
        }
    if(ans0) cout << -1 << endl;
    else if(ans1) cout << 1 << " " << ans1 << endl;
    else cout << 0 << " " << ans2 << endl;
    return 0;
}
