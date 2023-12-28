# include <bits/stdc++.h>

using namespace std;

# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second

int read()
{
# define C ch = getchar()
    int x = 0; char C;
    for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x;
}

const int N = 1e5 + 5;
int n , k , m , a[13][N] , tot;
int h[N*13] , cnt;
PII p[N + 10];

struct node
{
    int opt , x , y;
    node() {}
    node(int opt , int x , int y) : opt(opt) , x(x) , y(y) {}
} q[N];

namespace subtask1
{
    vector< int > vec[N + 10];
    bool solve()
    {
        if(n > 100) return 0;
        for(int i = 1; i <= k; i++) {vec[i].push_back(0); for(int j = 1; j <= n; j++) vec[i].push_back(a[i][j]);}
        for(int i = 1; i <= m; i++)
        {
            int opt = q[i].opt , x = q[i].x , y = q[i].y;
            if(opt == 1) {tot++; vec[tot].push_back(0); for(int j = 1; j <= n; j++) vec[tot].push_back(max(vec[x][j] , vec[y][j]));}
            else if(opt == 2) {tot++; vec[tot].push_back(0); for(int j = 1; j <= n; j++) vec[tot].push_back(min(vec[x][j] , vec[y][j]));}
            else cout << h[vec[x][y]] << '\n';
        }
        return 1;
    }
}

namespace subtask2
{
    int s[N + 10];
    bool solve()
    {
        for(int i = 1; i <= m; i++) if(q[i].opt == 2) return 0;
        for(int i = 1; i <= k; i++) s[i] = 1 << i - 1;
        for(int i = 1; i <= m; i++)
        {
            int opt = q[i].opt , x = q[i].x , y = q[i].y;
            if(opt == 1) s[++tot] = s[x] | s[y];
            else
            {
                int S = s[x] , res = 0;
                for(int j = 1; j <= k; j++) if(S & (1 << j - 1)) res = max(res , a[j][y]);
                cout << h[res] << '\n';
            }
        }
        return 1;
    }
}

int dfs(int x , int y)
{
    // cout << x << ' ' << y << ' ' << p[x].fi << ' ' << p[x].se << endl;
    if(p[x].fi > 0 && p[x].se < 0) 
    {
        int res;
        if(p[x].se == -1) 
        {
            res = 0;
            for(int i = 1; i <= 12; i++) if(p[x].fi & (1 << i - 1)) res = max(res , a[i][y]);
        }
        else 
        {
            res = 1e9;
            for(int i = 1; i <= 12; i++) if(p[x].fi & (1 << i - 1)) res = min(res , a[i][y]);
        }
        return res;
    }
    else if(p[x].fi > 0) return max(dfs(p[x].fi , y) , dfs(p[x].se , y));
    return min(dfs(-p[x].fi , y) , dfs(-p[x].se , y));
}

int main()
{
    freopen("compose.in" , "r" , stdin);
    freopen("compose.out" , "w" , stdout);
    n = read() , k = tot = read() , m = read();
    for(int i = 1; i <= k; i++) 
    {
        for(int j = 1; j <= n; j++)
        {
            a[i][j] = read();
            h[++cnt] = a[i][j];
        }
    }
    sort(h + 1 , h + cnt + 1) , cnt = unique(h + 1 , h + cnt + 1) - h - 1;
    for(int i = 1; i <= k; i++) {for(int j = 1; j <= n; j++) {a[i][j] = lower_bound(h + 1 , h + cnt + 1 , a[i][j]) - h;}}
    for(int i = 1; i <= m; i++) {q[i].opt = read() , q[i].x = read() , q[i].y = read();}
    if(subtask1::solve()) return 0;
    if(subtask2::solve()) return 0;
    for(int i = 1; i <= k; i++) p[i] = MP(1 << i - 1 , -1);
    for(int i = 1; i <= m; i++)
    {
        int opt = q[i].opt , x = q[i].x , y = q[i].y;
        if(opt == 1) 
        {
            tot++;
            if(p[x].fi > 0 && p[x].se == -1 && p[y].fi > 0 && p[y].se == -1) p[tot] = MP(p[x].fi | p[y].fi , -1);
            else p[tot] = MP(x , y);
        }
        else if(opt == 2)
        {
            tot++;
            if(p[x].fi > 0 && p[x].se == -2 && p[y].fi > 0 && p[y].se == -2) p[tot] = MP(p[x].fi | p[y].fi , -2);
            else p[tot] = MP(-x , -y);
        }
        else cout << h[dfs(x , y)] << '\n';
    }
    return 0;
}