#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int n, Q, a[maxn], b[maxn];
int mp[maxn * 2];

struct query{
    int opt, l, r, w;bool res;
    query(int opt = 0,int l = 0,int r = 0,int w = 0, bool res = 1):opt(opt),l(l),r(r),w(w),res(res){}
}q[maxn];
int val[maxn * 2], tot;

typedef long long ll;
struct BIT{
    ll c[maxn << 2];
    inline int lowbit(int x){return x & (-x);}
    void clear(){for(int i = 1;i <= n;i++)c[i] = 0;}
    void upd(int x,ll add){for(;x <= n;x += lowbit(x))c[x] += add;}
    ll qry(int x){ll ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
    ll query(int l,int r){return qry(r) - qry(l - 1);}
}tree;

mt19937 rnd(time(0));
int getint(ll x = 1){
    ll a = rnd() ^ rnd(), b = rnd() + (rnd() ^ x);
    int res = ((b ^ (x ^ b)) ^ ((a ^ x) ^ a)) % (1LL << 31LL);
    res = (res ^ (rnd() + x)) ^ (x ^ rnd());
    for(int i = (a + b + x + rnd()) % 6;i;i--){res /= 10;}
    return res % (1LL << 31LL);
}

signed main(){
    n = read();Q = read();
    for(int i = 1;i <= n;i++){val[++tot] = a[i] = read();}
    int opt, l, r, w;
    for(int i = 1;i <= Q;i++){
        opt = read(); l = read(); r = read();
        if(opt == 1){q[i] = query(opt,l,val[++tot] = r,0,0);}
        else q[i] = query(opt,l,r,read());
    }
    
    sort(val + 1,val + 1 + tot);tot = unique(val + 1,val + 1 + tot) - val - 1;
    for(int i = 1;i <= n;i++)a[i] = lower_bound(val + 1,val + 1 + tot,a[i]) - val;
    for(int i = 1;i <= Q;i++)if(q[i].opt == 1)q[i].r = lower_bound(val + 1,val + 1 + tot,q[i].r) - val;
// for(int i = 1;i <= n;i++)printf("%d ",a[i]);puts("");
// for(int i = 1;i <= Q;i++)printf("%d %d %d %d\n",q[i].opt,q[i].l,q[i].r,q[i].w);

    int times = 30;
    for(int ttt = 1;ttt <= times;ttt++){
        tree.clear();
        for(int i = 1;i <= tot;i++)
            mp[i] = getint(i * ttt);
        
            // printf("%lld\n",mp[i]);
    // cerr << "STEP : " << ttt << endl;
        for(int i = 1;i <= n;i++){tree.upd(i,mp[a[i]]);b[i] = a[i];}
        for(int i = 1;i <= Q;i++){
            opt = q[i].opt, l = q[i].l, r = q[i].r, w = q[i].w;
            if(opt == 1){tree.upd(l,mp[r] - mp[b[l]]);b[l] = r;}
            else{if(!q[i].res || (r - l + 1) % w || tree.query(l,r) % w)q[i].res = 0;}
        }
    }
    for(int i = 1;i <= Q;i++)
        if(q[i].opt == 2)
            puts(q[i].res ? "YES" : "NO");
    return 0;
}