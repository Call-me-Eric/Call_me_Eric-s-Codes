#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, S;

int head[maxn << 2], tot;
struct edge{
    int to, nexte;ll wei;
    edge(int to = 0,int ne = 0,ll we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 5];
void add(int u,int v,ll w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int id[maxn << 2][2],cntpoint;
int rev[maxn];
struct Segment_Tree{
    void build(int l,int r,int p,bool opt){
        id[p][opt] = ++cntpoint; if(l == r){rev[l] = p;return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1,opt);build(mid + 1,r,p << 1 | 1,opt);
        if(opt == 0){add(id[p][opt],id[p << 1][opt],0);add(id[p][opt],id[p << 1 | 1][opt], 0);}
        else{add(id[p << 1][opt],id[p][opt],0);add(id[p << 1 | 1][opt],id[p][opt],0);}
    }
    void query(int l,int r,int s,int t,int p,int u,ll wei,bool opt){
        if(s <= l && r <= t){
            if(opt == 0)add(id[rev[u]][opt ^ 1],id[p][opt],wei);
            else add(id[p][opt],id[rev[u]][opt ^ 1],wei);
            return;
        }
        int mid = l + r >> 1;
        if(s <= mid)query(l,mid,s,t,p << 1,u,wei,opt);
        if(mid < t)query(mid + 1,r,s,t,p << 1 | 1,u,wei,opt);
    }
    void query(int l,int r,int u,ll wei,bool opt){query(1,n,l,r,1,u,wei,opt);}
    void DEBUG(bool opt = 0,int l = 1,int r = n,int p = 1){
        printf("l = %d r = %d p = %d,opt = %d,id = %d\n",l,r,p,opt,id[p][opt]);
        if(l == r)return;
        int mid = l + r >> 1;
        DEBUG(opt,l,mid,p << 1);DEBUG(opt,mid  + 1,r,p << 1 | 1);
    }
}tree[2];

typedef pair<ll,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > que;
ll dis[maxn << 2];bool book[maxn << 2];

signed main(){
    n = read(); m = read(); S = read();int opt, l, r, u, w;
    tree[0].build(1,n,1,0); tree[1].build(1,n,1,1);
    // tree[0].DEBUG(0);tree[1].DEBUG(1);
    for(int i = 1;i <= n;i++){
        add(id[rev[i]][0],id[rev[i]][1],0);
        add(id[rev[i]][1],id[rev[i]][0],0);
    }
    for(int i = 1;i <= m;i++){
        opt = read();
        if(opt == 1){
            l = read(); r = read(); w = read();
            tree[0].query(r,r,l,w,0);
        }
        else{
            u =  read(); l = read(); r = read();w = read();
            tree[opt - 2].query(l, r, u, w, opt - 2);
        }
    }
    // for(int u = 1;u <= cntpoint;u++){
    //     for(int i = head[u];i;i = e[i].nexte){
    //         printf("%d -> %d, w = %lld\n",u,e[i].to,e[i].wei);
    //     }
    // }
    memset(dis,0x3f,sizeof(dis));
    dis[id[rev[S]][0]] = 0;que.push(make_pair(0,id[rev[S]][0]));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].wei;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                que.push(make_pair(dis[v],v));
            }
        }
    }
    for(int i = 1;i <= n;i++){
        if(dis[id[rev[i]][0]] == INF)dis[id[rev[i]][0]] = -1;
        printf("%lld ",dis[id[rev[i]][0]]);
    }
    return 0;
}