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
const int maxn = 1e4 + 10;
int n, m;
char ch[maxn / 3][maxn / 3];
vector<int> edg[maxn];
int fa[maxn], siz[maxn], cntedg[maxn];
int deg[maxn], val[3][maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void main(){
    n = read(); m = read();read(); read();
    for(int i = 1;i <= n + m;i++){fa[i] = i;siz[i] = 1;cntedg[i] = 0;}
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= m;j++){
            if(ch[i][j] == 'b'){
                deg[i]++;deg[j + n]++;
                int u = getf(i),v = getf(j + n);
                if(u != v){fa[u] = v;siz[v] += siz[u];cntedg[v] += cntedg[u];}
                cntedg[v]++;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(ch[i][j] == 'k'){
                int u = getf(i), v = getf(j + n);
                if(u == v){val[0][u]++;}
                else{val[1][u]++;val[1][v]++; val[2][i]++;val[2][j + n]++;}
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= n + m;i++){
        if(getf(i) == i && cntedg[i] >= siz[i])ans = max(ans,val[0][i] + val[1][i]);
        // printf("1 : ans = %d,i = %d,getf = %d\n",ans,i,getf(i));
    }
    for(int i = 1;i <= n + m;i++){
        if(deg[i] == 1){int f = getf(i);ans = max(ans,val[0][f] + val[1][f] - val[2][i]);}
        // printf("2 : ans = %d,i = %d\n",ans,i);
    }
    printf("%d\n",ans);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
7 3 4 5
bbb
..b
..b
k..
k..
k..
k..

3 3 4 2
k..
kk.
bbk

*/