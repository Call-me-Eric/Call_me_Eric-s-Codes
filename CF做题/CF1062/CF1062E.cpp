#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, q;

vector<int> edg[maxn];

int dfn[maxn], idx, fa[maxn][31], dep[maxn];
void dfs(int u,int f){
    dfn[u] = ++idx;fa[u][0] = f;dep[u] = dep[f] + 1;
    for(int i = 1;i <= 30;i++)fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int v : edg[u]){if(v != f)dfs(v, u);}
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 30;i + 1;i--)
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if(u == v)return u;
    for(int i = 30;i + 1;i--)
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

pair<int,int> minn[maxn][31][2], maxx[maxn][31][2];
void init(){
    // memset(minn,0x3f,sizeof(minn));memset(maxx,-0x3f,sizeof(maxx));
    for(int i = 1;i <= n;i++){
        minn[i][0][0] = maxx[i][0][0] = make_pair(dfn[i],i);
        minn[i][0][1] = make_pair(0x3f3f3f3f,0);
        maxx[i][0][1] = make_pair(-0x3f3f3f3f,0);
    }
    for(int len = 1;len <= 30;len++){
        for(int i = 1;i + (1 << len) - 1 <= n;i++){
            vector<pair<int,int> > vec;vec.clear();
            vec.push_back(minn[i][len - 1][0]);
            vec.push_back(minn[i + (1 << (len - 1))][len - 1][0]);
            if(len != 1){
                vec.push_back(minn[i][len - 1][1]);
                vec.push_back(minn[i + (1 << (len - 1))][len - 1][1]);
            }
            sort(vec.begin(),vec.end(),less<pair<int,int> >());
            minn[i][len][0] = vec[0];minn[i][len][1] = vec[1];

            vector<pair<int,int> > vec1;vec1.clear();
            vec1.push_back(maxx[i][len - 1][0]);
            vec1.push_back(maxx[i + (1 << (len - 1))][len - 1][0]);
            if(len != 1){
                vec1.push_back(maxx[i][len - 1][1]);
                vec1.push_back(maxx[i + (1 << (len - 1))][len - 1][1]);
            }
            sort(vec1.begin(),vec1.end(),greater<pair<int,int> >());
            maxx[i][len][0] = vec1[0];maxx[i][len][1] = vec1[1];
        }
    }
}

int lg[maxn];

signed main(){
    n = read(); q = read();lg[1] = 0;lg[0] = -1;
    for(int i = 2;i <= n;i++){lg[i] = lg[i >> 1] + 1;;edg[read()].push_back(i);}
    dep[0] = -1;dfs(1, 0); init(); int u, v;
    for(int i = 1;i <= q;i++){
        u = read(); v = read();
        int len = lg[v - u + 1];
        vector<pair<int,int> > vec;vec.clear();
        vec.push_back(minn[u][len][0]);
        vec.push_back(minn[v - (1 << (len)) + 1][len][0]);
        vec.push_back(minn[u][len][1]);
        vec.push_back(minn[v - (1 << (len)) + 1][len][1]);
        sort(vec.begin(),vec.end(),less<pair<int,int> >());
        vector<pair<int,int> > vec1;vec1.clear();
        vec1.push_back(maxx[u][len][0]);
        vec1.push_back(maxx[v - (1 << (len)) + 1][len][0]);
        vec1.push_back(maxx[u][len][1]);
        vec1.push_back(maxx[v - (1 << (len)) + 1][len][1]);
        sort(vec1.begin(),vec1.end(),greater<pair<int,int> >());
        if(vec[0].second == vec[1].second){vec[1] = vec[2];}
        if(vec1[0].second == vec1[1].second){vec1[1] = vec1[2];}
        int lca1 = LCA(vec[0].second,vec1[1].second), lca2 = LCA(vec[1].second,vec1[0].second);

        if(dep[lca1] > dep[lca2]){printf("%d %d\n",vec1[0].second,dep[lca1]);}
        else printf("%d %d\n",vec[0].second,dep[lca2]);
        // printf("DEBUG:%d %d %d %d %d %d\n",vec[0].second,vec[1].second,vec1[0].second,vec1[1].second,lca1,lca2);
    }
    return 0;
}