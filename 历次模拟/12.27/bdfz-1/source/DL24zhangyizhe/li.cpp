# include <bits/stdc++.h>

using namespace std;

# define ll long long

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 1e6 + 5;
int n , m;
vector< int > e[N] , g[N];
int cnt , vis[N] , flag;
ll ans;
int ecnt , eu[N] , ev[N];
int hcnt , hu[N] , hv[N];

void dfs(int u , int fat)
{
    vis[u] = 1 , cnt++;
    for(int v : e[u]) if(v ^ fat)
    {
        if(vis[v]) flag = 1;
        else dfs(v , u);
    } 
}

bool check_circle()
{
    int Flag = 0;
    for(int i = 1; i <= n; i++) if(!vis[i])
    {
        cnt = 0 , flag = 0 , dfs(i , 0);
        if(flag) Flag = 1;
        if(!flag) ans = (ans + 1ll * cnt * (cnt + 1) / 2); 
    }
    return Flag;
}

namespace subtask1
{
    bool solve()
    {
        if(n > 4) return 0;
        cout << 1 << ' ' << n;
        return 1;
    }
}

int main()
{
    n = read() , m = read();
    for(int i = 1 , u , v; i <= m; i++) 
    {
        ecnt++;
        eu[ecnt] = u = read() , ev[ecnt] = v = read();
        e[u].push_back(v) , e[v].push_back(u);
    }
    if(!check_circle()) return cout << 0 << ' ' << ans , 0;
    if(subtask1::solve()) return 0;
    return 0;
}