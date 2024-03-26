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
const int maxn = 2e5 + 10;
int n, m;
int a[maxn], b[maxn];
typedef priority_queue<int,vector<int>,greater<int> > prique;
struct kmaxque{
    prique que;int siz, sum;
    void init(int sz){siz = sz;sum = 0;while(!que.empty())que.pop();}
    void push(int x){
        que.push(x);sum += x;
        if(que.size() > siz){sum -= que.top();que.pop();}
    }
    void pop(){que.pop();}
    int top(){return que.top();}
    int getans(){return sum;}
    int size(){return que.size();}
    bool empty(){return que.empty();}
};
namespace Subtask1{
kmaxque solve(int l,int r,int k){
    kmaxque que;que.init(k);
    if(l == r){que.push(0);return que;}
    int mid = l + r >> 1;
    kmaxque lque = solve(l,mid,k);que = solve(mid + 1,r,k);
    while(!lque.empty()){que.push(lque.top());lque.pop();}
    int lp = mid, rp = mid + 1;
    while(lp >= l){
        rp = mid + 1;
        while(rp <= r && (que.size() < k || b[lp] - b[rp] > que.top())){que.push(b[lp] - b[rp]);rp++;}
        lp--;
    }
    vector<int> vec;lp = l,rp = mid + 1;
    while(lp <= mid && rp <= r){
        if(b[lp] < b[rp]){vec.push_back(b[lp++]);}
        else vec.push_back(b[rp++]);
    }
    while(lp <= mid)vec.push_back(b[lp++]);
    while(rp <= r)vec.push_back(b[rp++]);
    for(int i = 0;i < vec.size();i++){b[l + i] = vec[i];}vec.clear();
    return que;
}
void main(){
    int opt, u , v, x;
    for(int t = 1;t <= m;t++){
        opt = read(); u = read(), v = read(); x = read();
        if(opt == 1){for(int i = u;i <= v;i++)a[i] += x;}
        else{
            for(int i = u;i <= v;i++)b[i] = a[i];
            auto ans = solve(u,v,x);
            printf("%lld\n",ans.getans());
        }
    }
}
};
namespace Subtask2{
struct Segment_Tree{
    struct node{
        int ans, maxx, minn, tag;
        node(int ans = 0,int maxx = 0,int minn = 0,int tag = 0
        ):ans(ans),maxx(maxx),minn(minn),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(max(max(l.ans,r.ans),l.maxx - r.minn),max(l.maxx,r.maxx),min(l.minn,r.minn));}
    void addtag(int p,int tag){d[p].maxx += tag;d[p].minn += tag;d[p].tag += tag;}
    void pushdown(int p){addtag(p << 1,d[p].tag);addtag(p << 1 | 1,d[p].tag);d[p].tag = 0;}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0,a[l],a[l]);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){addtag(p,upd);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;pushdown(p);
        if(t <= mid)return query(l,mid,s,t,p << 1);
        if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
}tree;
void main(){
    tree.build(1,n,1);
    int opt, u, v, x;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(), v = read(); x = read();
        if(opt == 1){tree.update(1,n,u,v,1,x);}
        else printf("%lld\n",tree.query(1,n,u,v,1).ans);
    }
}
};
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){a[i] = read();}
    bool cases = (n <= 2000 && m <= 2000);
    if(cases){Subtask1::main();return;}
    else{Subtask2::main();return;}
    return;
}
};
bool edmemory;
signed main(){
    freopen("smart.in","r",stdin);
    freopen("smart.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
6 5
1 1 4 5 1 4
2 4 6 3
2 1 6 2
1 1 4 -2
1 4 6 1
2 2 5 5
*/
