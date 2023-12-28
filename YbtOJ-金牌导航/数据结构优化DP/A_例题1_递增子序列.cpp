#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 123456789;
int n, a[maxn], m;
vector<int> vec;
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int upd){for(;x <= n;x += lowbit(x))c[x] = (c[x] + upd) % mod;}
    int qry(int x){int ans = 0;for(;x;x -= lowbit(x))ans = (ans + c[x]) % mod;return ans;}
    void clear(){for(int i = 0;i <= n;i++)c[i] = 0;}
}tree[101];
signed main(){
    while(scanf("%lld%lld",&n,&m) != EOF){
        for(int i = 1;i <= n;i++){vec.push_back(a[i] = read());}
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        int ans = 0;
        for(int i = 1;i <= n;i++){
            int x = lower_bound(vec.begin(),vec.end(),a[i]) - vec.begin() + 1;
            tree[1].upd(x,1);
            for(int j = 1;j <= m;j++)
                tree[j].upd(x,tree[j - 1].qry(x - 1));
        }
        ans = tree[m].qry(n);
        printf("%lld\n",ans);
        for(int i = 1;i <= m;i++)tree[i].clear();vec.clear();
    }
    return 0;
}