#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int col[maxn], a[maxn];

vector<int> edg[maxn];
int dfn[maxn], idx, siz[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx;siz[u] = 1;
    for(int v : edg[u])if(v != f){dfs(v, u);siz[u] += siz[v];}
}

int len;
struct query{
    int l, r, k, id;
    query(int l = 0,int r = 0,int k = 0,int id = 0):l(l),r(r),k(k),id(id){}
    friend bool operator < (query a,query b){
        if(a.l / len != b.l / len)return a.l < b.l;
        return ((a.l / len) & 1) ? a.r > b.r : a.r < b.r;
    }
}q[maxn];

int cnt[maxn], res[maxn];
int ans[maxn];

void del(int x){res[cnt[col[x]]]--;cnt[col[x]]--;}
void add(int x){cnt[col[x]]++;res[cnt[col[x]]]++;}

signed main(){
    n = read();m = read();int u, v;len = sqrt(n);
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v=  read();
        edg[v].push_back(u);edg[u].push_back(v);
    }
    // puts("1111111");
    dfs(1, 0);for(int i = 1;i <= n;i++)col[dfn[i]] = a[i];
    for(int i = 1;i <= m;i++){u = read(); v = read();q[i] = query(dfn[u],dfn[u] + siz[u] - 1,v,i);}
    sort(q + 1,q + 1 + m);
    // puts("2222222");
    int l = 0, r = 0;
    for(int i = 1;i <= m;i++){
        while(q[i].l < l){l--;add(l);}
        while(q[i].r > r){r++;add(r);}
        while(q[i].l > l){del(l);l++;}
        while(q[i].r < r){del(r);r--;}
        ans[q[i].id] = res[q[i].k];
    }
    for(int i = 1;i <= m;i++){printf("%d\n",ans[i]);}
    return 0;
}