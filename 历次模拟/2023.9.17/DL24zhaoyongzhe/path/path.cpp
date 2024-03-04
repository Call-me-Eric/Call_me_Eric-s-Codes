#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 510,mod = 998244353, maxm = 60;
int n, m;
int a[maxn], b[maxn], c[maxn], d[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = (res * x) % mod;}
        x = (x * x) % mod; a >>= 1;
    }
    return res;
}
// int id[maxm][maxm], cnt;
// int dist[maxm * maxm][maxm * maxm];
// void add(int u,int v,int w){dist[u][v] = w;}
// void addd(int u,int v,int w){add(u,v,w);add(v,u,w);}

signed main(){
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);
    n = read(); m = read();
    int ans = qpow(n,3) * ((n * n % mod - 1 + mod) % mod) * qpow(3,mod - 2) % mod;
    if(m == 0){printf("%lld\n",ans);return 0;}
    for(int i = 1;i <= m;i++){
        a[i] = read(); b[i] = read(); c[i] = read(); d[i] = read();
        if(a[i] < c[i]){
            if(b[i] < d[i]){ans = (ans - (a[i] * b[i] % mod) * ((n - c[i] + 1) * (n - d[i] + 1) % mod) % mod + mod) % mod;}
            else{ans = (ans - (a[i] * (n - b[i] + 1) % mod) * ((n - c[i] + 1) * d[i] % mod) % mod + mod) % mod;}
        }
        else{
            if(b[i] < d[i]){ans = (ans - ((n - a[i] + 1) * b[i] % mod) * (c[i] * (n - d[i] + 1) % mod)% mod + mod) % mod;}
            else{ans = (ans - ((n - a[i] + 1) * (n - b[i] + 1) % mod) * (c[i] * d[i] % mod) % mod + mod) % mod;}
        }
    }
    printf("%lld\n",ans % mod);
    return 0;
}
/*
    memset(dist,0x3f,sizeof(dist));
    for(int i = 1;i <= n * n;i++)dist[i][i] = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            id[i][j] = ++cnt;
            if(i != 1)addd(id[i][j],id[i - 1][j],1);
            if(j != 1)addd(id[i][j],id[i][j - 1],1);
        }
    }
    for(int i = 1;i <= m;i++){
        a[i] = read(); b[i] = read(); c[i] = read(); d[i] = read();
        addd(id[a[i]][b[i]],id[c[i]][d[i]],abs(a[i] - c[i]) + abs(b[i] - d[i]) - 1);
    }
    for(int k = 1;k <= cnt;k++){
        for(int i = 1;i <= cnt;i++){
            for(int j = 1;j <= cnt;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= cnt;i++){
        for(int j = 1;j <= cnt;j++){
            ans = (dist[i][j] % mod + ans) % mod;
            // printf("dist[%lld][%lld] = %lld\n",i,j,dist[i][j]);
        }
    }
    printf("%lld\n",ans / 2);
    // printf("%lld\n",cnt);
*/