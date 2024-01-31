#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;

int fa[maxn];
int getf(int x){return x == fa[x] ? x : fa[x] = getf(fa[x]);}

int siz[maxn], buc[maxn];

int cost[maxn], val[maxn], tot;
int f[maxn], ans = 0x3f3f3f3f;

void dfs(int u){
    // printf("u = %d",u);
    if(u * 10 + 4 > n)return;
    u = u * 10 + 4;if(f[u] != 0x3f3f3f3f)ans = min(ans,f[u]);
    dfs(u);u /= 10;
    if(u * 10 + 7 > n)return;   
    u = u * 10 + 7;if(f[u] != 0x3f3f3f3f)ans = min(ans,f[u]);
    dfs(u);
}

signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){fa[i] = i;}
    int u, v;
    for(int i = 1;i <= m;i++){
        u = getf(read()), v = getf(read());
        if(u != v)fa[u] = v;
    }
    for(int i = 1;i <= n;i++)siz[getf(i)]++;
    for(int i = 1;i <= n;i++)if(getf(i) == i){buc[siz[i]]++;}
    for(int i = 1;i <= n;i++){
        if(buc[i]){
            for(int j = 0;j <= 30;j++){
                if(buc[i] >= (1 << j)){
                    val[++tot] = (1 << j) * i;
                    cost[tot] = (1 << j);
                    buc[i] -= (1 << j);
                }
            }
            if(buc[i] != 0){val[++tot] = buc[i] * i;cost[tot] = buc[i];}
        }
    }
    memset(f,0x3f,sizeof(f));f[0] = 0;
    for(int i = 1;i <= tot;i++)
        for(int j = n;j >= val[i];j--)
            f[j] = min(f[j],f[j - val[i]] + cost[i]);
    // printf("tot=%d\n",tot);
    // for(int i = 1;i <= tot;i++){printf("%d %d\n",cost[i],val[i]);}
    // for(int i = 1;i <= n;i++)printf("f[%d]=%d,fa[i]=%d\n",i,f[i],fa[i]);
    dfs(0);
    printf("%d\n",ans == 0x3f3f3f3f ? -1 : (ans - 1));
    return 0;
}