#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10,maxm = 1e6 + 10;
int q;
struct Segment_Tree{
    struct node{
        int ans, sum;
        node(int ans = 0,int sum = 0
        ):ans(ans),sum(sum){}
    }d[maxm << 2];
    node mergenode(node l,node r){return node(max(r.ans,l.ans + r.sum),l.sum + r.sum);}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(l,0);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){d[p].ans += upd;d[p].sum += upd;return;}
        int mid = l + r >> 1;
        if(pos <= mid)update(l,mid,pos,p << 1,upd);
        else update(mid + 1,r,pos,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void build(){build(0,1e6,1);}
    void update(int pos,int upd){update(0,1e6,pos,1,upd);}
    node query(int s,int t){return query(0,1e6,s,t,1);}
}tree;
pair<int,int> knight[maxn];
void main(){
    q = read();char opt;int u, v;
    tree.build();
    for(int i = 1;i <= q;i++){
        opt = getchar();while(opt != '+' && opt != '-' && opt != '?')opt = getchar();
        if(opt == '+'){
            u = read() - 1, v = read();
            knight[i] = make_pair(u,v);
            tree.update(u,v);
        }
        if(opt == '-'){
            u = read();
            tree.update(knight[u].first,-knight[u].second);
        }
        if(opt == '?'){
            u = read() - 1;
            printf("%lld\n",tree.query(0,u).ans - u);
        }
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