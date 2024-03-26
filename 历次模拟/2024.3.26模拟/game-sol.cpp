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
const int maxn = 4e5 + 10;
int n, q, O;
struct Segment_Tree{
    struct node{
        int ch[2], cnt, sum;
        node(int sum = 0,int cnt = 0,int c0 = 0,int c1 = 0):cnt(cnt),sum(sum){ch[0] = c0;ch[1] = c1;}
    }d[maxn * 30];
    #define C(p,x) d[p].ch[x]
    node mergenode(node l,node r,node p = node()){return node(l.sum * ((r.cnt & 1) ? -1 : 1) + r.sum,l.cnt + r.cnt,p.ch[0],p.ch[1]);}
    int tot,rt;
    void update(int l,int r,int pos,int &p,int upd,int cnt){
        if(!p)p = ++tot;
        if(l == r){d[p].cnt += cnt;d[p].sum = upd * (d[p].cnt & 1);return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,C(p,0),upd,cnt);
        else update(mid + 1,r,pos,C(p,1),upd,cnt);
        d[p] = mergenode(d[C(p,0)],d[C(p,1)],d[p]);
    }
    node query(int l,int r,int s,int t,int p){
        if(!p)return node();
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,C(p,0));
        if(mid < s)return query(mid + 1,r,s,t,C(p,1));
        return mergenode(query(l,mid,s,t,C(p,0)),query(mid + 1,r,s,t,C(p,1)));
    }
    void update(int pos,int upd,int cnt){update(0,2e9,pos,rt,upd,cnt);}
    node query(int l,int r){return query(0,2e9,l,r,rt);}
}tree;
int deg[maxn];
vector<pair<pair<int,int> , int>> edg;
void main(){
    n = read(); q = read(); O = read();
    int lastans = 0;
    tree.update(0,0,n);
    for(int i = 1;i <= q;i++){
        int opt = read(), u = read() ^ (O * lastans), v, w;
        if(opt == 1){v = read() ^ (O * lastans), w = read();edg.push_back(make_pair(make_pair(u,v),w));}
        else{u--;v = edg[u].first.second, w = -edg[u].second;u = edg[u].first.first;}
        tree.update(deg[u],deg[u],-1);if(u != v)tree.update(deg[v],deg[v],-1);
        deg[u] += w;deg[v] += w;
        tree.update(deg[u],deg[u],1);if(u != v)tree.update(deg[v],deg[v],1);
        printf("%d\n",lastans = tree.d[tree.rt].sum / 2);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}