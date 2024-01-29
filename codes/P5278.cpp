#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
#define ll long long
const ll mod = 998244353;
const int maxn = 3e5 + 10;
int Gcd(int x,int y){return __gcd(x, y);}
int a[maxn], n, m;
struct Segment_Tree{
    struct node{
        ll squsum;int sum, _gcd;
        int maxx,minn;
        node(ll sq = 0,int sum = 0,int mx = 0,int mn = 0,int _gcd = 0):squsum(sq), sum(sum),maxx(mx),minn(mn),_gcd(_gcd){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node((l.squsum + r.squsum) % mod,l.sum + r.sum,max(l.maxx,r.maxx),min(l.minn,r.minn),Gcd(l._gcd,r._gcd));}
    void build(int l,int r,int p){
        if(l == r){d[p] = node(((ll)a[l] * a[l]) % mod,a[l],a[l],a[l],abs(a[l + 1] - a[l]));return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    void update(int l,int r,int pos,int p,int upd){
        if(l == r && l == pos){a[l] = upd;d[p] = node(((ll)a[l] * a[l]) % mod,a[l],a[l],a[l],abs(a[l + 1] - a[l]));return;}
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
    void update(int pos,int upd){
        update(1,n,pos,1,upd);
        if(pos != 1)update(1,n,pos - 1,1,a[pos - 1]);
    }
    node query(int l,int r){return query(1,n,l,r,1);}
}tree;
signed main(){
    n = read(); m = read(); int opt, l, r, k, cnt = 0;
    for(int i = 1;i <= n;i++)a[i] = read();
    tree.build(1,n,1);
    for(int i = 1;i <= m;i++){
        opt = read();l = read() ^ cnt; r = read() ^ cnt;
        if(opt == 1)tree.update(l,r);
        else{
            k = read() ^ cnt;
            if(l == r){puts("Yes");cnt++;continue;}
            Segment_Tree::node tmp = tree.query(l,r);
            int u = tmp.minn, v = tmp.maxx;
            if(k == 0){
                if(u == v)puts("Yes"),cnt++;
                else puts("No");
                continue;
            }
// puts("111111");
            tmp._gcd = tree.query(l,r - 1)._gcd;
            if(tmp._gcd == 0 || (tmp._gcd % k != 0)){puts("No");continue;}
// puts("22222");
            if((v - u) % k){puts("No");continue;}
// puts("33333");
// printf("x = %lld\n",x);
// printf("x = %lld\n",x);
// printf("expect = %lld  facts = %lld \n",(x * 6ll + y) % mod,tmp.squsum * 6ll % mod);
            ll x = (ll)(r - l + 1ll) * u % mod * u % mod;
            x = (x + (ll)k * u % mod * (r - l) % mod * (r - l + 1ll) % mod) % mod;
            int y = (ll)k * k % mod * (r - l + 1ll) % mod * (r - l) % mod * (2ll * (r - l) % mod + 1ll) % mod;
            if((x * 6ll % mod + y) % mod != tmp.squsum * 6ll % mod){puts("No");continue;}
            puts("Yes");cnt++;
        }
    }
    return 0;
}