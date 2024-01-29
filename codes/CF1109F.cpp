#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f =-1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
struct LCT{
    struct node{
        int fa, ch[2];int tag;
        node(int fa = 0,int c0 = 0,int c1 = 0,int tag = 0):fa(fa),tag(tag){ch[0] = c0;ch[1] = c1;}
    }d[maxn];
    #define FA(p) d[p].fa
    #define C(p,x) d[p].ch[x]
    void maintain(int p){}
    int get(int p){return p == C(FA(p),0) ? 0 : (p == C(FA(p),1) ? 1 : -1);}
    void pushdown(int p){
        if(d[p].tag){
            swap(C(p,0),C(p,1)); d[p].tag = 0;
            d[C(p,0)].tag ^= 1;d[C(p,1)].tag ^= 1;
        }
    }
    void pushdownall(int p){
        if(get(p) != -1)pushdownall(FA(p));
        pushdown(p);
    }
    void connect(int p,int f,int chk){FA(p) = f;if(chk == 1 || chk == 0)C(f,chk) = p;}
    void rotate(int x){
        int y = FA(x), z = FA(y), chkx = get(x), chky = get(y);
        int u = chkx != -1 ? C(x,chkx ^ 1) : 0;
        connect(u, y, chkx);connect(y, x, chkx ^ 1);connect(x,z,chky);
        maintain(y);maintain(x);
    }
    void splay(int p){
        pushdownall(p);
        for(int f = FA(p);f = FA(p),get(p) != -1;rotate(p))
            if(get(f) != -1)rotate(get(f) == get(p) ? f : p);
    }
    void access(int p){
        int rs = 0;
        while(p){
            splay(p); C(p,1) = rs; rs = p;
            maintain(p);p = FA(p);
        }
    }
    void makeroot(int p){access(p);splay(p);d[p].tag ^= 1;}
    void split(int x,int y){
        makeroot(x);
        access(y);splay(y);
    }
    int findroot(int p){
        access(p);splay(p);
        while(C(p,0)){pushdown(p);p = C(p,0);}
        splay(p);return p;
    }
    bool check(int x,int y){makeroot(x);return findroot(y) == x;}
    bool link(int x,int y){
        makeroot(x);if(findroot(y) == x)return false;
        // puts("11242324314312423141234123");
        FA(x) = y;return true;
    }
    void cut(int x,int y){
        if(findroot(x) != findroot(y))return;
        split(x, y);if(FA(x) != y || C(x, 1))return;
        FA(x) = C(y,0) = 0;
        maintain(x);maintain(y);
    }
}lct;
int n, m;
struct Segment_Tree{
    struct node{
        int minn, cnt;int tag;
        node(int minn = 0x3f3f3f3f,int cnt = 1,int tag = 0):minn(minn),cnt(cnt),tag(tag){}
    }d[maxn << 2];
    node mergenode(node l,node r){
        node ans = l;
        if(l.minn > r.minn){ans = r;}
        if(l.minn == r.minn){ans.cnt += r.cnt;}
        ans.tag = 0;return ans;
    }
    void change(int p,int upd){if(p >= (maxn << 2))return;d[p].minn += upd;d[p].tag += upd;}
    void pushdown(int p){
        if(d[p].tag){
            change(p << 1,d[p].tag); change(p << 1 | 1,d[p].tag); d[p].tag = 0;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(0);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1); build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int s,int t,int p,int upd){
        // printf("l = %d  r = %d s = %d t = %d, p = %d,upd = %d\n",l,r,s,t,p,upd);
        if(s <= l && r <= t){change(p,upd);return;}
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
    void update(int l,int r,int upd){if(l > r)return;update(1,n,l,r,1,upd);}
    node query(int l,int r){return query(1,n,l,r,1);}
    void DEBUG(int l = 1,int r = n,int p = 1){
        printf("[%d,%d],p = %d,minn = %d,cnt = %d,tag = %d\n",l,r,p,d[p].minn,d[p].cnt,d[p].tag);
        if(l == r)return;int mid = l + r >> 1;
        DEBUG(l,mid,p << 1);DEBUG(mid + 1,r,p << 1 | 1);
    }
}tree;
int a[1001][1001];
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0, 1,-1, 0};
vector<int> edg[maxn];
int R[maxn];
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("tmp.in","r",stdin);
    freopen("tmp.out","w",stdout);
    #endif
    n = read(); m = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            a[i][j] = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            for(int k = 0;k < 4;k++){
                int nx = i + dx[k], ny = j + dy[k];
                if(nx < 1 || ny < 1 || nx > n || ny > m)continue;
                edg[a[i][j]].push_back(a[nx][ny]);
            }
        }
    }
    int l = 0, r = 0;n = n * m;
    while(l < n){
        for(int v : edg[l]){lct.cut(l,v);}l++;
        while(r < n){
            r++;bool book = true;
            for(int v : edg[r]){
                if(v >= l && v < r && !lct.link(v, r)){book = false;}
            }
            // printf("book = %d\n",book);
            if(!book){
                for(int v : edg[r]){lct.cut(v, r);}
                r--;break;
            }
            // printf("r = %d\n",r);
        }
        R[l] = r;
        // printf("l = %d\n",l);
    }
    // puts("111113423412334123");
    long long ans = 0;tree.build(1,n,1);Segment_Tree::node lst;
    for(l = n;l;l--){
        tree.update(l,R[l],1);
        for(int v : edg[l]){
            if(v > l && v <= R[l]){tree.update(v, R[l],-1);}
        }
        auto tmp = tree.query(l,R[l]);
        if(tmp.minn < 1)printf("l = %d : %d %d %d %d\n",l,lst.minn,lst.cnt,tmp.minn,tmp.cnt);
        assert(tmp.minn >= 1);
        ans += 1ll * tmp.cnt;lst = tmp;
    }
    printf("%lld\n",ans);
    return 0;
}