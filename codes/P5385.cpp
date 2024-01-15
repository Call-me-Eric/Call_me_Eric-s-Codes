#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
struct LCT{
    struct node{
        int fa, ch[2]; int tag, minn, val;
        node(int minn = 0x3f3f3f3f,int val = 0x3f3f3f3f,int fa = 0,int c0 = 0,int c1 = 0,bool tag = 0
        ):fa(fa),tag(tag),minn(minn),val(val){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define C(p,x) d[p].ch[x]
    #define FA(p) d[p].fa
    void maintain(int p){d[p].minn = min(min(d[C(p,0)].minn,d[C(p,1)].minn),d[p].val);}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}//return p == Fa(p,1),but return -1 when p is the root of Splay
    void connect(int p,int f,int chk){FA(p) = f; if(chk == 0 || chk == 1)C(f,chk) = p;}
    void pushdown(int p){
        if(d[p].tag){
            swap(C(p,0),C(p,1));
            if(C(p,0))d[C(p,0)].tag ^= 1;
            if(C(p,1))d[C(p,1)].tag ^= 1;
            d[p].tag = 0;
        }
    }
    void pushdownall(int p){
        if(get(p) != -1) pushdownall(FA(p));
        pushdown(p);
    }

    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u,y,chkx);connect(y,x,chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        pushdownall(p);
        while(get(p) != -1){
            int f = FA(p);
            if(get(f) == -1)rotate(p);
            else if(get(f) == get(p)){rotate(f);rotate(p);}
            else {rotate(p);rotate(p);}
        }
    }
    void access(int p){
        int rs = 0;
        while(p){
            splay(p);C(p,1) = rs;maintain(p);
            rs = p;p = FA(p);
        }
    }
    void makeroot(int p){
        access(p); splay(p);
        swap(C(p,0),C(p,1));
        if(C(p,0))d[C(p,0)].tag ^= 1;
        if(C(p,1))d[C(p,1)].tag ^= 1;
    }
    void split(int x,int y){
        makeroot(x);
        access(y);splay(y);
    }
    int findroot(int p){
        access(p);splay(p);
        while(C(p,0)){pushdown(p),p = C(p,0);}
        splay(p);return p;
    }
    bool connected(int x,int y){return findroot(x) == findroot(y);}
    bool link(int x,int y){
        makeroot(x);
        if(findroot(y) == x) return false;
        FA(x) = y;return true;
    }
    void cut(int x,int y){
        if(findroot(x) != findroot(y))return;
        split(x, y);
        if(FA(x) != y || C(x,1))return;
        FA(x) = C(y,0) = 0;
        maintain(x);maintain(y);return;
    }
    node query(int x,int y){split(x, y);return d[y];}
    void update(int p,int val){splay(p);d[p].val = val;maintain(p);}
}lct;
int n, m, q, t, lastans;
pair<int,int> edg[maxn];
int head[maxn];
struct Segment_Tree{
    int tot;
    struct node{
        int summ;int ch[2];
        node(int summ = 0,int c0 = 0,int c1 = 0):summ(summ){ch[0] = c0;ch[1] = c1;}
    }d[maxn * 30];
    #define C(p,x) d[p].ch[x]
    node mergenode(node l,node r){return node(l.summ + r.summ);}
    void insert(int l,int r,int pos,int &p,int p1,int val){
        if(!p) p = ++tot;
        if(l == r && l == pos){d[p] = node(val);return;}
        int mid = l + r >> 1,chk = pos > mid;
        if(pos <= mid)insert(l,mid,pos,C(p,0),C(p1,0),val);
        else insert(mid + 1,r,pos,C(p,1),C(p1,1),val);
        C(p,chk ^ 1) = C(p1,chk ^ 1);
        d[p] = mergenode(d[C(p,0)],d[C(p,1)]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,C(p,0));
        if(mid < s)return query(mid + 1,r,s,t,C(p,1));
        return mergenode(query(l,mid,s,t,C(p,0)),query(mid + 1,r,s,t,C(p,1)));
    }
    void insert(int &p,int p1,int pos,int val){insert(1,m,pos,p,p1,val);}
    node query(int l,int r,int p){return query(1,m,l,r,p);}
}tree;
signed main(){
    n = read(); m = read(); q = read(); t = read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        edg[i] = make_pair(u, v);
        int lst = head[i - 1];
        if(lct.connected(u, v)){
            int x = lct.query(u, v).minn;
            lct.cut(edg[x].first,x + n);lct.cut(edg[x].second,x + n);
            tree.insert(head[i],lst,x,0);lst = head[i];
        }
        tree.insert(head[i],lst,i,1);
        lct.link(u,i + n);lct.link(i + n, v);
        lct.update(i + n,i);
    }
    for(int i = 1;i <= q;i++){
        int u = read(), v = read();
        if(t > 0){
            u = (u + t * lastans) % m + 1;
            v = (v + t * lastans) % m + 1;
        }
        if(u > v)swap(u, v);
        printf("%d\n",lastans = (n - tree.query(u, v,head[v]).summ));
    }
    return 0;
}