#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
bool st;
#define ll long long
namespace Subtask1{
    const ll mod = 1e9 + 7;
    ll qpow(ll x,ll a){
        ll res = 1;
        while(a){
            if(a & 1)res = res * x % mod;
            x = x * x % mod;a >>= 1;
        }
        return res;
    }
    ll f(ll a){
        if(a < 1)return 1;
        ll res = 0;
        if(a & 1){res = ((qpow(3,a / 2 + 1) + ((a - 1) % 4 == 0 ? -1 : 1) + mod) % mod * f(a / 2) % mod) % mod;}
        else{
            res = (qpow(3,a / 2 + 1) + (a % 4 == 0 ? -1 : 1) + mod) % mod * f(a / 2 - 1) % mod;
            res += qpow(3,a / 2) * (a % 4 == 0 ? 1 : -1);
            while(res < mod)res += mod;
        }
        return res % mod;
    }
    void main(){
        ll a = read() - 2;
        printf("%lld\n",f(a) * 12 % mod);
    }
};
namespace Subtask3{
    const int maxn = 1e5 + 10;
    int n, m, a[maxn];
    struct Segment_Tree{
        struct node{
            ll maxx, lmax, rmax, summ;
            node(ll summ = 0,ll lmax = 0,ll rmax = 0,ll maxx = 0):summ(summ),lmax(lmax),rmax(rmax),maxx(maxx){}
        }d[maxn << 2];
        node mergenode(node l,node r){return node(l.summ + r.summ,max(l.lmax,l.summ + r.lmax),max(r.rmax,r.summ + l.rmax),max(max(l.maxx,r.maxx),l.rmax + r.lmax));}
        void build(int l,int r,int p){
            if(l == r){d[p] = node(a[l],a[l],a[l],a[l]);return;}
            int mid = l + r >> 1;
            build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
            d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
        }
        node query(int l,int r,int s,int t,int p){
            if(s <= l && r <= t)return d[p];
            int mid = l + r >> 1;
            if(t <= mid)return query(l,mid,s,t,p << 1);
            if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
            return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
        }
    }tree;
    void main(){
        n = read();m = read();
        for(int i = 1;i <= n;i++)a[i] = read();
        tree.build(1,n,1);
        for(int i = 1;i <= m;i++){
            int u = read(), v = read();
            printf("%lld\n",tree.query(1,n,u,v,1).maxx);
        }
    }
};
namespace Subtask5{
    const int maxn = 1e3 + 10;
    int n;
    vector<pair<int,ll> > edg[maxn];
    ll f[maxn][2];
    void dfs(int u,int fa){
        for(auto i : edg[u]){
            int v = i.first;ll w = i.second;
            if(v != fa){
                dfs(v, u);
                if(f[u][0] < f[v][0] + w){
                    f[u][1] = f[u][0];
                    f[u][0] = f[v][0] + w;
                }
                else if(f[u][1] < f[v][0] + w){
                    f[u][1] = f[v][0] + w;
                }
            }
        }
    }
    void main(){
        n = read();int u, v, w;
        for(int i = 1;i < n;i++){
            u = read(); v = read(); w = read();
            edg[u].push_back(make_pair(v, w));
            edg[v].push_back(make_pair(u, w));
        }
        dfs(1 ,1); ll ans = -0x3f3f3f3f;
        for(int i = 1;i <= n;i++){
            ans = max(ans,f[i][0] + f[i][1]);
        }
        printf("%lld\n",ans);
    }
};
namespace Subtask7{
    const int maxn = 2e3 + 10, maxm = 3e3 + 10;
    int n, m;
    struct edge{
        int to, nexte;ll wei;
        edge(int to = 0,int ne = 0,ll we = 0):to(to),nexte(ne),wei(we){}
    }e[maxm * 2];
    int tot, head[maxn];
    void add(int u,int v,ll w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
    ll dis[maxn];bool book[maxn];
    priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > que;
    ll dijsktra(int S,int T){
        memset(dis,0x3f,sizeof(dis));
        dis[S] = 0;que.push(make_pair(dis[S],S));
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
        return dis[T];
    }
    void main(){
        n = read(), m = read();int u, v, w;
        for(int i = 1;i <= m;i++){
            u = read(); v = read(); w = read();
            add(u, v, w);add(v, u ,w);
        }
        printf("%lld\n",dijsktra(1,n));
    }
};
namespace Subtask9{
    const int maxn = 2e3 + 10;
    char ch[maxn];
    int maxx[30];
    void main(){
        scanf("%s",ch + 1);int n = strlen(ch + 1), len = 0;
        for(int i = 1;i <= n;i++){
            if(ch[i] != ch[i - 1]){
                if(i != 1)maxx[ch[i - 1] - 'a'] = max(maxx[ch[i - 1] - 'a'],len);
                len = 1;
            }
            else len++;
        }
        maxx[ch[n] - 'a'] = max(maxx[ch[n] - 'a'],len);
        int max1 = 0, max2 = 0;
        for(int i = 0;i < 26;i++){
            if(maxx[i] > max1){
                max2 = max1;max1 = maxx[i];
            }
            else if(maxx[i] > max2){
                max2 = maxx[i];
            }
        }
        if(max1 <= 2)max1 = 0;
        if(max2 <= 2)max2 = 0;
        printf("%d\n",max1 / 2 * 2 + max2 / 2 * 2);
    }
};
bool ed;
signed main(){
    freopen("crack.in","r",stdin);
    freopen("crack.out","w",stdout);
    int T = read();
    if(T == 1){Subtask1::main();return 0;}
    if(T == 3){Subtask3::main();return 0;}
    if(T == 5){Subtask5::main();return 0;}
    if(T == 7){Subtask7::main();return 0;}
    if(T == 9){Subtask9::main();return 0;}
    return 0;
}