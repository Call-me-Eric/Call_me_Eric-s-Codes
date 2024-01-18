#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool stmemory;
const int maxn = 4e5 + 10;
int n, m;

inline int getid(int i,int j){return (i - 1) * m + j;}
vector<int> mp[maxn];
//L=0,U=1,R=2,D=3
inline int optid(char ch){if(ch == 'R')return 0;if(ch == 'D')return 1;if(ch == 'L')return 2;if(ch == 'U')return 3;}
const int dx[4] = { 0,-1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
char ch[maxn];
vector<int> edg[maxn];
int fa[maxn];
int dfn[maxn], idx, low[maxn];

void dfs(int u){dfn[u] = ++idx;for(int v : edg[u])dfs(v);low[u] = idx;}

struct scanline{
    int x, y, opt;
    scanline(int x = 0,int y = 0,int opt = 0
    ):x(x),y(y),opt(opt){}
};
vector<scanline> vec[maxn];
struct Segment_Tree{
    struct node{
        int l, r;int minn, cnt;//minn 是区间tag决定是否用儿子更新，cnt是有面积的位置总数。
        node(int l = 0,int r = 0,int minn = 0,int cnt = 0):l(l),r(r),minn(minn),cnt(cnt){}
    }d[maxn << 2];
    void pushup(int p){
        if(d[p].minn){d[p].cnt = d[p].r - d[p].l + 1;}
        else d[p].cnt = d[p << 1].cnt + d[p << 1 | 1].cnt;
    }
    void build(int l,int r,int p){
        d[p] = node(l, r);if(l == r)return;
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        pushup(p);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].minn += upd;pushup(p);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        pushup(p);
    }
    int query(){return d[1].cnt;}
}tree;
bool edmemory;
signed main(){
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost.\n";
    n = read();m = read();
    for(int i = 1;i <= n;i++){
        mp[i].resize(m + 1); scanf("%s",ch + 1);
        for(int j = 1;j <= m;j++) mp[i][j] = optid(ch[j]);
    }
    // puts("11111111");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            for(int k = 0;k < 4;k++){
                int nx = i + dx[k] * 2, ny = j + dy[k] * 2;
                if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
                if(mp[nx][ny] != (k + 2) % 4)continue;
                edg[getid(i, j)].push_back(getid(nx,ny));
                fa[getid(nx,ny)] = getid(i, j);
            }
        }
    }
    // puts("22232322222");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(!dfn[getid(i,j)]){
                int u = getid(i, j);
                while(fa[u])u = fa[u];
                dfs(u);
            }
        }
    }
    // puts("3333343333343");
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if((i + j) & 1){
                int nx = dx[mp[i][j]] + i, ny = dy[mp[i][j]] + j;
                int xl = dfn[getid(i, j)], xr = low[getid(i, j)];
                int yu = dfn[getid(nx,ny)],yd = low[getid(nx,ny)];
                // printf("(%d, %d), (%d, %d)\n",i,j,nx,ny);
                // printf("%d %d %d %d\n",xl,xr,yu,yd);
                vec[xl    ].push_back(scanline(yu,yd,1));
                vec[xr + 1].push_back(scanline(yu,yd,-1));
            }
        }
    }
    // puts("4444444444");
    int ans = 0;tree.build(1,idx,1);
    for(int i = 1;i <= idx;i++){
        for(auto v : vec[i]){tree.update(1,idx,v.x,v.y,1,v.opt);}
        ans += tree.query();
    }
    printf("%lld\n",ans);
    return 0;
}