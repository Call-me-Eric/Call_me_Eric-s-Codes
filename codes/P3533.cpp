#include<bits/stdc++.h>
using namespace std;
inline  int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ( ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, m;
vector<int> edg[maxn], rev[maxn];

struct DSU{
    int fa[maxn];
    DSU(){for(int i = 1;i <= n;i++)fa[i] = i;}
    int getf(int x){return fa[x] == x  ? x : fa[x] = getf(fa[x]);}
    bool query(int x,int y){return getf(x) == getf(y);}
    void merge(int x,int y){if(!query(x, y))fa[getf(x)] = getf(y);}
}dsu;

int anc[maxn], dep[maxn], fa[21][maxn];
int mp[maxn], from[maxn], idx;
int stk[maxn], top, tot[maxn];
bool book[maxn];
bool getring(int);
void dfs(int u,int root){
    for(int v : rev[u]){
        if(!mp[v]){
            dep[v] = dep[u] + 1;
            fa[0][v] = u;anc[v] = root;
            dfs(v, root);
        }
    }
}
int id[maxn],cntblock;
bool getring(int u){
    book[u] = 1;
// printf("u = %d\n",u);
    for(int v : edg[u]){
        if(!book[v]){from[v] = u;if(getring(v))return 1;}
        else{
            int tmp = u;top = idx = 0;
            while(tmp != v){
                stk[++top] = tmp;
                tmp = from[tmp];
            }stk[++top] = v;
            for(int i = top;i >= 1;i--){mp[stk[i]] = ++idx;}
            tot[id[dsu.getf(stk[1])]] = idx;
            return 1;
        }
    }
    return 0;
}
void solve(vector<int> vec){
    getring(vec[0]);//找环
    for(int i : vec)//维护子树基本信息
        if(mp[i]){
            fa[0][i] = i;dep[i] = 0;
            anc[i] = i;dfs(i,i);
        }
    for(int j = 1;j <= 20;j++)
        for(int i : vec)
            fa[j][i] = fa[j - 1][fa[j - 1][i]];
    
    // printf("ringid = %d\n",id[dsu.getf(vec[0])]);
    // for(int i : vec){printf("mp[%d] = %d\n",i,mp[i]);}
    // for(int i : vec){printf("anc[%d] = %d\n",i,anc[i]);}
    // for(int i : vec){printf("dep[%d] = %d\n",i,dep[i]);}
    // for(int i : vec){printf("fa[0][%d] = %d\n",i,fa[0][i]);}
    // printf("totring = %d\n",tot[id[dsu.getf(vec[0])]]);
    // puts("");
}

int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v]){
            u = fa[i][u];
            v = fa[i][v];
        }
    return fa[0][u];
}

vector<int> vec[maxn];
signed main(){
    n = read(); m = read();int u;dsu = DSU();
    for(int i = 1;i <= n;i++){
        u = read(); dsu.merge(u, i);
        edg[i].push_back(u);
        rev[u].push_back(i);
    }
    
    for(int i = 1;i <= n;i++){
        if(!id[dsu.getf(i)])id[dsu.getf(i)] = ++cntblock;
        vec[id[dsu.getf(i)]].push_back(i);
    }
    for(int i = 1;i <= cntblock;i++){solve(vec[i]);}

    int x, y;
    for(int i = 1;i <= m;i++){
        x = read(); y = read();
        if(!dsu.query(x, y)){puts("-1 -1");continue;}
        if(anc[x] == anc[y]){
            int lca = LCA(x, y);
            printf("%d %d\n",dep[x] - dep[lca],dep[y] - dep[lca]);
            continue;
        }
        int a = mp[anc[x]], b = mp[anc[y]];
        int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
        if(a < b){
            x1 = dep[x] + b - a;y1 = dep[y];
            x2 = dep[x];y2 = dep[y] + tot[id[dsu.getf(anc[x])]] + a - b;
        }
        else{
            x1 = dep[x];y1 = dep[y] + a - b;
            x2 = dep[x] + tot[id[dsu.getf(anc[x])]] + b - a;y2 = dep[y];
        }
        // printf("x1 = %d, y1 = %d, x2 = %d, y2 = %d\n",x1,y1,x2,y2);
        if(max(x1,y1) == max(x2,y2)){
            if(min(x1,y1) == min(x2,y2)){if(x1 < y1){x1 = x2;y1 = y2;}}
            else{if(min(x1,y1) > min(x2,y2)){x1 = x2;y1 = y2;}}
        }
        else{if(max(x1,y1) > max(x2,y2)){x1 = x2;y1 = y2;}}
        printf("%d %d\n",x1,y1);
    }

    return 0;
}