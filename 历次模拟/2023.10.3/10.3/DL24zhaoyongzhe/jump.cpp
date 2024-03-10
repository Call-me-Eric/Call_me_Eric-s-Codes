#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxm = 8e5 + 10;
int n;
int x[maxn];

int head[maxn], tot;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxm << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int edg[110][110];

signed main(){
    freopen("jump.in","r",stdin);
    freopen("jump.out","w",stdout);
    n = read();
if(n > 100){
    for(int i = 1;i <= n;i++){
        x[i] = read();
    }
    printf("%d\n",n - 1);
}   
else{
    memset(edg,0x3f,sizeof(edg));
    for(int i = 1;i <= n;i++){
        x[i] = read();
        for(int j = max(1,i - x[i]);j <= min(i + x[i],n);j++){
            edg[i][j] = 1;
        }
    }
    for(int k = 1;k <= n;k++){
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                if(edg[i][j] > edg[i][k] + edg[k][j])
                    edg[i][j] = edg[i][k] + edg[k][j];
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            ans = max(ans,min(edg[i][j],edg[j][i]));
        }
    }
    printf("%d\n",ans);
}
    return 0;
}