#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 4e4 + 10;
int n, m;

map<pair<int,int>, int> mp;
int head[maxn], tot,tot1,tot2, head1[maxn];
struct edge{int from,to ,nexte, id;edge(int from = 0,int to = 0,int ne = 0,int id = 0):from(from),to(to),nexte(ne),id(id){}}e[maxn],e1[maxn],e2[maxn];
void add(int u,int v,int id){e[++tot] = edge(u,v,head[u],id);head[u] = tot;}
// void add1(int u,int v,int id){e1[++tot1] = edge(u,v,head1[u],id);head1[u] = tot1;}

int fat[maxn];
int getf(int x){return x == fat[x] ? x : fat[x] = getf(fat[x]);}

int fa[maxn][21], dep[maxn];
bool book[maxn];
void dfs(int u,int f){
    fa[u][0] = f; dep[u] = dep[f] + 1;
    for(int i = 1;i <= 20;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(f == v || dep[v])continue;
        // book[mp[make_pair(u,v)]] = book[mp[make_pair(v,u)]] = true;
        // fat[getf(v)] = getf(u); 
        dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if(u == v)return u;
    for(int i = 20;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int cf[maxn];
void dfs2(int u,int f){
    book[u] = true;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;if(v == f || book[v])continue;
        dfs2(v,u);cf[u] += cf[v];
    }
}

int ans[maxn],cnt;

signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        mp[make_pair(u,v)] = i;
        mp[make_pair(v,u)] = i;
        e1[i] = edge(u,v);
    }
    for(int i = 1;i <= n;i++)fat[i] = i;
    for(int i = 1;i <= m;i++){
        int u = e1[i].from, v = e1[i].to;
        int fu = getf(u), fv = getf(v);
        if(fu != fv){
            add(u,v,i); add(v,u,i);
            fat[fv] = fu;
        }
        else e2[++tot2] = edge(e1[i].from,e1[i].to,0,i);
    }
    for(int i = 1;i <= n;i++){if(!dep[i])dfs(i,i);}
    // for(int i = 1;i <= tot;i++){
    //     if(book[mp[make_pair(e[i].from,e[i].to)]]){
    //         add1(e[i].from,e[i].to,e[i].id);
    //         add1(e[i].to,e[i].from,e[i].id);
    //     }
    //     else {e2[++tot2] = e[i];}
    // }
    // for(int i = 1;i <= n;i++){printf("dep[%d] = %d\n",i,dep[i]);}
    // printf("tot=%d\n",tot);
    int st, ed, L, sum = 0, idd = 0;
    for(int i = 1;i <= tot2;i++){
        u = e2[i].from, v = e2[i].to;int id = e2[i].id;
        if(getf(u) != getf(v))continue;
        int lca = LCA(u,v), dist = dep[u] + dep[v] - 2 * dep[lca];
        if((dist % 2) == 0){
            // printf("%d %d %d\n",u,v,dist);
            sum++; st = u; ed = v; L = lca;idd = id;
            cf[u]++;cf[v]++;cf[lca] -= 2;
        }
        else{
            cf[u]--;cf[v]--;cf[lca] += 2;
        }
    }
    for(int i = 1;i <= n;i++){if(!book[i])dfs2(i,i);}
    if(sum == 0){
        printf("%d\n",m);
        for(int i = 1;i <= m;i++)printf("%d ",i);
    }else if(sum == 1){
        for(int i = st;i != L;i = fa[i][0]){
            if(cf[i] == 1){
                ans[++cnt] = mp[make_pair(i,fa[i][0])];
            }
        }
        for(int i = ed;i != L;i = fa[i][0]){
            if(cf[i] == 1){
                ans[++cnt] = mp[make_pair(i,fa[i][0])];
            }
        }
        ans[++cnt] = idd;
        sort(ans + 1,ans + 1 + cnt);
        printf("%d\n",cnt);
        for(int i = 1;i <= cnt;i++){printf("%d ",ans[i]);}
    }else{
        // printf("sum=%d\n",sum);
        // for(int i = 1;i <= n;i++){printf("cf[%d] = %d\n",i,cf[i]);}
        for(int i = 1;i <= n;i++){
            if(cf[i] == sum){
                ans[++cnt] = mp[make_pair(i,fa[i][0])];
            }
        }
        sort(ans + 1,ans + 1 + cnt);
        printf("%d\n",cnt);
        for(int i = 1;i <= cnt;i++)printf("%d ",ans[i]);
    }
    return 0;
}