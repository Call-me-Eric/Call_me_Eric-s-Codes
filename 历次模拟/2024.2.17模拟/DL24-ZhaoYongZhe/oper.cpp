#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, INF = 0x3f3f3f3f;
int n, m;
int p[maxn], a[maxn], v[maxn];
int dis[maxn][maxn];
int f[maxn][maxn * 10];
void solve(){
    n = read(); m = read();int ring = 0;
    for(int i = 1;i <= n;i++){p[i] = read();}
    for(int i = 1;i <= m;i++)a[i] = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++)dis[i][j] = INF;
        int x = i;dis[i][x] = 0;
        while(dis[i][p[x]] == INF){dis[i][p[x]] = dis[i][x] + 1;x = p[x];}
        if(i == a[1]){ring = dis[i][x] + 1 - dis[i][p[x]];}
    }
    for(int i = 1;i <= n;i++){
        bool flag = true;
        for(int j = 1;j <= m;j++){
            if(dis[a[j]][i] == INF){flag = false;break;}
            v[j] = dis[a[j]][i];
            if(v[j - 1] >= v[j])v[j] += (v[j - 1] - v[j]) / ring * ring;
        }
        if(!flag){printf("-1 ");continue;}
        int N = ring;
        for(int j = 1;j <= N;j++)f[0][j] = INF;
        for(int j = 1;j <= m;j++){
            for(int k = 0,p = 0,minn = INF;k <= N;k++){
                while(v[j - 1] + ring * p <= v[j] + ring * k && p <= N){
                    minn = min(minn,v[j] + ring * (k - p) - v[j - 1] + f[j - 1][p]);
                    p++;
                }
                f[j][k] = minn;minn += ring;
            }
            for(int k = N,p = N,minn = INF;k >= 0;k--){
                while(v[j - 1] + ring * p > v[j] + ring * k && p >= 0){
                    minn = min(minn,f[j - 1][p]);
                    p--;
                }
                f[j][k] = min(f[j][k],minn);
            }
        }
        int ans = INF;
        for(int j = 0;j <= N;j++)ans = min(ans,f[m][j]);
        printf("%d ",ans);
    }
    puts("");
}
void main(){int T = read();while(T--){solve();}}
};
bool edmemory;
signed main(){
    freopen("oper.in","r",stdin);
    freopen("oper.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}