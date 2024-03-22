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
const int maxn = 5e5 + 10;
int n, m;
struct edge{
    int u, v, id;
    edge(int u = 0,int v = 0,int id = 0
    ):u(u),v(v),id(id){}
    friend bool operator < (edge a,edge b){return a.id < b.id;}
};
vector<edge> edg[maxn];
edge e[maxn], ed[maxn];
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(), v = read(), w = read();
        e[i] = edge(u,v,w);
        edg[w].push_back(edge(u,v,i));
    }
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= 5e5;i++){
        for(edge j : edg[i]){
            u = j.u, v = j.v, w = j.id;
            ed[j.id] = edge(getf(u),getf(v), i);
        }
        for(edge j : edg[i]){
            u = j.u, v = j.v, w = j.id;
            if(getf(u) != getf(v))fa[getf(u)] = getf(v);
        }
    }
    int q = read();
    for(int i = 1;i <= n;i++)fa[i] = i;
    while(q--){
        int x = read();vector<edge> id;
        bool flag = true;
        for(int i = 1;i <= x;i++){
            w = read();
            u = ed[w].u, v = ed[w].v;
            id.push_back(edge(u,v,ed[w].id));
        }
        sort(id.begin(),id.end());
        for(int i = 0;i < id.size() && flag;){
            int j = i;
            for(;j < id.size() && id[j].id == id[i].id;j++){
                if(getf(id[j].u) == getf(id[j].v)){flag = false;break;}
                fa[getf(id[j].u)] = getf(id[j].v);
            }
            while(i < j){fa[id[i].u] = id[i].u;fa[id[i].v] = id[i].v;i++;}
        }
        puts(flag ? "YES" : "NO");
    }
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