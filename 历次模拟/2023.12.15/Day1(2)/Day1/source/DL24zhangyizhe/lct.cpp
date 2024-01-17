# include <bits/stdc++.h>

using namespace std;

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 2e5 + 5 , S = 450;
int n , q , ans[N];
vector< int > e[N];
int vis[N] , num[N] , fa[N] , tot;

struct node
{
    int l , r , id;
    node() {}
    node(int l , int r , int id) : l(l) , r(r) , id(id) {}
    bool operator < (node const &rhs)
    {
        if((l - 1) / S + 1 == (rhs.l - 1) / S + 1)
        {
            if(((l - 1) / S + 1) % 2 == 1) return r < rhs.r;
            return r > rhs.r;
        }
        return l < rhs.l;
    }
} a[N];

namespace subtask1
{
    int vis[1005];
    void dfs(int u)
    {
        vis[u] = 0;
        for(int v : e[u]) if(vis[v]) dfs(v);
    }
    bool solve()
    {
        if(n > 1e3) return 0;
        for(int i = 1 , l , r , cnt; i <= q; i++)
        {
            l = read() , r = read() , cnt = 0;
            for(int j = l; j <= r; j++) vis[j] = 1;
            for(int j = l; j <= r; j++) if(vis[j]) dfs(j) , cnt++;
            cout << cnt << '\n';
        }
        return 1;
    }
}

void Add(int u)
{
    if(!u) return ;
    num[fa[u]]++ , vis[u] = 1;
    int res = num[u] + vis[fa[u]];
    tot -= res - 1;
}

void Del(int u)
{
    if(!u) return ;
    num[fa[u]]-- , vis[u] = 0;
    int res = num[u] + vis[fa[u]];
    tot += res - 1;
}

void dfs(int u , int fat)
{
    fa[u] = fat;
    for(int v : e[u]) if(v ^ fat) dfs(v , u);
}

int main()
{
    freopen("lct.in" , "r" , stdin);
    freopen("lct.out" , "w" , stdout);
    n = read() , q = read();
    for(int i = 1 , u , v; i < n; i++) u = read() , v = read() , e[u].push_back(v) , e[v].push_back(u);
    if(subtask1::solve()) return 0;
    dfs(1 , 0);
    for(int i = 1; i <= q; i++)
    {
        a[i].l = read() , a[i].r = read() , a[i].id = i;
    }
    sort(a + 1 , a + n + 1);
    for(int i = 1 , L = 0 , R = 0; i <= q; i++)
    {
        //cout << a[i].l << ' ' << a[i].r << ' ' << a[i].id << endl;
        while(L < a[i].l) Del(L++);
        while(L > a[i].l) Add(--L);
        while(R < a[i].r) Add(++R);
        while(R > a[i].r) Del(R--);
        ans[a[i].id] = tot;
    }
    for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}
