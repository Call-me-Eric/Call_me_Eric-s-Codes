#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch <'0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n;
vector<int> edg[maxn];
int fa[maxn], dep[maxn], son[maxn], siz[maxn];
void dfs(int u,int f){
    fa[u] = f;dep[u] = dep[f] + 1;siz[u] = 1;
    for(int v : edg[u]){
        if(v != f){
            dfs(v, u);  siz[u] += siz[v];
            son[u] = siz[son[u]] > siz[v] ? son[u] : v;
        }
    }
}
int depth;
void dfs1(int u){
    int v = u, d = 0;
    while(son[v])v = son[v];
    cout << "d " << v << endl;cin >> d;
    if(d == 1){cout << "! " << fa[v] << endl;exit(0);}
    int deplca = (depth + dep[v] - d) / 2, tmp = v;
    while(dep[v] != deplca)v = fa[v];
    if(d == 0 || deplca == depth){cout << "! " << v << endl;exit(0);}
    cout << "s " << v << endl;int t;cin >> t;
    if(son[v] == t){
        for(int i = 1;i <= d;i++){tmp = fa[tmp];}
        cout << "! " << tmp << endl;exit(0);
    }
    dfs1(t);
}
signed main(){
    cin >> n;int u, v;
    for(int i = 1;i < n;i++){
        cin >> u >> v;
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dep[0] = -1;dfs(1, 0);
    cout << "d 1" << endl;cin  >> depth;
    if(!depth){cout << "! 1" << endl;return 0;}
    dfs1(1);
    return 0;
}