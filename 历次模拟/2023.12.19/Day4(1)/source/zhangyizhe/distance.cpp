# include <bits/stdc++.h>

using namespace std;

# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second

const int N = 1e4 + 5;
int n , m , k , top , sta[N];
PII a[N];
map< PII , int > mp;
int dis[510][510] , vis[510] , pre[510] , h[510];

bool check(int i , int j)
{
    if(i == j) return 0;
    if(a[j].fi < a[i].fi && a[j].se < a[i].se) return 0;
    return 1;
}

bool comp(int u , int v , int f)
{
    memcpy(h , dis[v] , sizeof(h));
    h[f]++;
    while(h[f] == 2) h[f] = 0 , h[f + 1]++ , f++;
    // for(int i = 10; i; i--) cout << h[i]; cout << endl << f << ' ' <<  v << endl;
    for(int i = 500; i; i--)
    {
        if(h[i] != dis[u][i]) return h[i] < dis[u][i];
    }
    return 0;
}

void trans(int u , int v , int f)
{
    memcpy(h , dis[v] , sizeof(h));
    h[f]++;
    while(h[f] == 2) h[f] = 0 , h[f + 1]++ , f++;
    memcpy(dis[u] , h , sizeof(h));
}

void SPFA()
{
    for(int i = 2; i <= k; i++) for(int j = 0; j <= 500; j++) dis[i][j] = 1;
    queue< int > Q;
    Q.push(1);
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop(); 
        // cout << u << endl;
        vis[u] = 0;
        for(int v = 1; v <= k; v++) if(check(u , v))
        {   
            if(comp(v , u , max(abs(a[u].fi - a[v].fi) , abs(a[u].se - a[v].se))))
            {
                trans(v , u , max(abs(a[u].fi - a[v].fi) , abs(a[u].se - a[v].se)));
                pre[v] = u;
                if(!vis[v]) vis[v] = 1 , Q.push(v);
            }
        }
    }
}

void Prt(int x)
{
    if(pre[x]) Prt(pre[x]);
    sta[++top] = x;
}

int main()
{
    freopen("distance.in" , "r" , stdin);
    freopen("distance.out" , "w" , stdout);
    cin >> n >> m >> k;
    for(int i = 1; i <= k; i++)
    {
        cin >> a[i].fi >> a[i].se;
        mp[MP(a[i].fi , a[i].se)] = i;
    }
    SPFA();
    Prt(k);
    cout << top << '\n';
    for(int i = 1; i <= top; i++) cout << sta[i] << ' ';
    return 0;
}