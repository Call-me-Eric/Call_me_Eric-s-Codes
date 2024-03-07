#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxk = 1e2 + 10, mod = 998244353;

int n, m, q, len;
int a[maxn], sum[maxn];
map<int,int> mp;
int tot, rev[maxk];
struct query{
    int l, r, id;
    query(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
    friend bool operator < (query a,query b){
        if(a.l / len == b.l / len)return (a.l / len) & 1 ? a.r > b.r :a.r < b.r;
        return a.l < b.l;
    }
};
vector<query> vec[maxk];
int f[maxn * 3];
int inv[maxn * 3];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = (res * x) %mod;
        x = (x * x) % mod;a >>= 1;
    }
    return res;
}

int cnt[maxn], res, ans[maxn];
void add(int x,int col){cnt[x]++;res = (res * (rev[col] + sum[x] - cnt[x] + 1) % mod);}
void del(int x,int col){res = (res * inv[rev[col] + sum[x] - cnt[x] + 1] % mod);cnt[x]--;}

signed main(){
    freopen("slim.in","r",stdin);
    freopen("slim.out","w",stdout);
    n = read(); m = read(); q = read();
    int mx = 0, l, r, w;
    for(int i = 1;i <= n;i++){a[i] = read();sum[a[i]]++;}
    for(int i = 1;i <= q;i++){
        l = read(); r = read(); w = read();
        if(!mp[w]){mp[w] = ++tot; rev[tot] = w;}
        vec[mp[w]].push_back(query(l,r,i));
        mx = max(mx, w);
    }
    
    inv[0] = inv[1] = 1;
    for(int i = 2;i <= n + mx;i++){inv[i] = (mod - mod / i) * inv[mod % i] % mod;}

    for(int i = 1;i <= tot;i++){
        f[n] = 1; len = max(1LL,(int)(n / (int)sqrt(vec[i].size())));
        for(int j = n - 1;j;j--)f[j] = f[j + 1] * (n + m * rev[i] % mod - j) % mod;
        sort(vec[i].begin(),vec[i].end());
        memset(cnt,0,sizeof(cnt));
        l = 1, r = 0;res = 1;
        for(auto j : vec[i]){
            while(l > j.l)add(a[--l],i);
            while(r < j.r)add(a[++r],i);
            while(l < j.l)del(a[l++],i);
            while(r > j.r)del(a[r--],i);
            ans[j.id] = res * f[(j.r - j.l + 1)] % mod;
        }
    }

    for(int i = 1;i <= q;i++)printf("%lld\n",ans[i]);
    return 0;
}