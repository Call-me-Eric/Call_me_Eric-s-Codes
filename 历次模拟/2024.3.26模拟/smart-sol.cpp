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
struct Segment_Tree{
    struct node{
        int ans, maxx,maxpos, minn,minpos, x, y, tag;
        node(int ans = 0,int maxx = 0,int maxpos = 0,int minn = 0,int minpos = 0,int x = 0,int y = 0,int tag = 0
        ):ans(ans),maxx(maxx),minn(minn),tag(tag),x(x),y(y),maxpos(maxpos),minpos(minpos){}
    }d[maxn << 2];
    node mergenode(node l,node r){
        node ans = node();
        
        if(l.ans < r.ans)ans = r;else ans = l;
        ans.tag = 0;
        if(l.maxx - r.minn > ans.ans){
            ans.ans = l.maxx - r.minn;
            ans.x = l.maxpos;ans.y = r.minpos;
        }

        ans.minn = min(l.minn,r.minn);
        ans.minpos = l.minn < r.minn ? l.minpos : r.minpos;

        ans.maxx = max(l.maxx,r.maxx);
        ans.maxpos = l.maxx > r.maxx ? l.maxpos : r.maxpos;
        return ans;
    }
    void addtag(int p,int tag){d[p].maxx += tag;d[p].minn += tag;d[p].tag += tag;}
    void pushdown(int p){addtag(p << 1,d[p].tag);addtag(p << 1 | 1,d[p].tag);d[p].tag = 0;}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0,a[l],l,a[l],l,l,l);return;}
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
    void update(int l,int r,int upd){update(1,n,l,r,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
struct node{
    int u, d, l, r;
    int ans, opt, x, y;
    node(){u = d = l = r = ans = opt = x = y = 0;}
    node(int up,int dw,int lt = -1,int rt = -1){
        u = up;d = dw;l = lt;r = rt;
        opt = (lt == -1) ? 1 : 2;
        if(lt == -1){l = up;r = dw;}
        if(opt == 1){
            auto tmp = tree.query(u,d);
            ans = tmp.ans;x = tmp.x; y = tmp.y;
        }
        else{
            auto tl = tree.query(u,d), tr = tree.query(l,r);
            ans = tl.maxx - tr.minn;x = tl.maxpos; y = tr.minpos;
        }
    }
    friend bool operator < (node a,node b){return a.ans < b.ans;}
    friend bool operator > (node a,node b){return a.ans > b.ans;}
};
priority_queue<node,vector<node>,less<node> > que;
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++){a[i] = read();}
    tree.build(1,n,1);
    for(int i = 1;i <= m;i++){
        int opt = read(), l = read(), r = read(), k = read();
        if(opt == 1){tree.update(l,r,k);}
        else{
            while(!que.empty())que.pop();
            que.push(node(l,r));
            int ans = 0;
            while(k && !que.empty()){
                node u = que.top();que.pop();
                // cerr << "u.ans = " << u.ans << " u.opt = " << u.opt << "[" << u.x << "," << u.y << "]" << endl;
                // cerr << "[" << u.u << "," << u.d << "],[" << u.l << "," << u.r << "]\n";
                if(u.d < u.u || u.r < u.l)continue;
                ans += u.ans;k--;
                if(u.opt == 1){
                    if(u.x > u.l){
                        que.push(node(u.l,u.x - 1));
                        que.push(node(u.l,u.x - 1,u.x,u.r));
                    }
                    if(u.x != u.y){que.push(node(u.x,u.x));}
                    if(u.x < u.y - 1){que.push(node(u.x,u.x,u.x + 1,u.y - 1));}
                    if(u.y < u.r){que.push(node(u.x,u.x,u.y + 1,u.r));}
                    if(u.x < u.r){que.push(node(u.x + 1,u.r));}
                }
                else{
                    if(u.u < u.x){que.push(node(u.u,u.x - 1,u.l,u.r));}
                    if(u.l < u.y){que.push(node(u.x,u.x,u.l,u.y - 1));}
                    if(u.y < u.r){que.push(node(u.x,u.x,u.y + 1,u.r));}
                    if(u.x < u.d){que.push(node(u.x + 1,u.d,u.l,u.r));}
                }
            }
            printf("%lld\n",ans);
        }
    }
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
