#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, k;
const int maxn = 510, mod = 1e9 + 7;
int dp[maxn][maxn];
int l[maxn],r[maxn], cnt;
struct seg{
    int l,r;
}a[maxn];
struct cmp{
    bool operator()(seg a,seg b){
        return a.r < b.r;
    }
};
bool solve(int statement){
    int tot = 0, tmp = 0;
    for(int x = statement;x;x -= x & (-x)){
        tmp = (int)log2(x & (-x));
        a[++tot].l = l[tmp];
        a[tot].r = r[tmp];
    }
    int r = 0,ans = 0;
    sort(a + 1,a + 1 + tot, cmp());
    for(int i = 1;i <= tot;i++){
        if(r < a[i].l){
            r = a[i].r;
            ans++;
        }
    }
    return ans == k;
}
signed main(){
    freopen("seg.in","r",stdin);
    freopen("seg.out","w",stdout);
    n = read(); k = read();
    cnt = -1;
    for(int i = 1;i <= n;i++)
        for(int j = i;j <= n;j++){
            l[++cnt] = i;r[cnt] = j;}
    int ans = 0;
    for(int i = 0;i < (1 << (1 + cnt));i++){
        if(solve(i)){ans++;ans = ans % mod;}
    }
    printf("%lld\n",ans);
    return 0;
}