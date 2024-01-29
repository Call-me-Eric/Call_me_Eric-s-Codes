#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<int> edg[maxn], to[maxn];
int vis[maxn], bel[maxn], deg[maxn];
void tarjan(int u){
    vis[u] = 1;bel[u] = 1;
    for(int v : edg[u]){
        if(!bel[v]){to[u].push_back(v);deg[v]++;}
        if(!vis[v])tarjan(v);
    }
    bel[u] = 0;
}
vector<int> A;
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){int u = read(), v = read();edg[u].push_back(v);}
    for(int i = 1;i <= n;i++)if(!vis[i])tarjan(i);
    for(int i = 1;i <= n;i++)if(!deg[i])A.push_back(i);
    while(A.size() > 1){
        int u = A.back();A.pop_back();
        int v = A.back();A.pop_back();
        printf("? %d %d\n",u, v);fflush(stdout);
        if(!read()){swap(u, v);}A.push_back(u);
        for(int w : to[v]){if(!--deg[w])A.push_back(w);}
    }
    printf("! %d\n",A.back());fflush(stdout);
    return 0;
}