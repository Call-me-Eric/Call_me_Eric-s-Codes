#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, maxm = 6e6 + 10;
int a[maxn], n;
int prime[maxm], tot;
bool book[maxm];
signed main(){
    // freopen("divisor.in","r",stdin);
    // freopen("divisor.out","w",stdout);
    n = read();int mx = 0;long long ans = 0;
    for(int i = 1;i <= n;i++)mx = max(mx,(a[i] = read()));
    ans = (mx == 1 ? 0 : mx); mx = maxm - 10;
    // cerr << "mx = " << mx << endl;
    for(int i = 2;i <= mx;i++){
        if(!book[i]){prime[++tot] = i;}
        for(int j = 1;j <= tot && i * prime[j] <= mx;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    // cerr << "tot = " << tot << endl;
    for(int i = 1;i <= tot;i++){
        long long res = 0;
        for(int j = 1;j <= n;j++)
            if(a[j] % prime[i] == 0)res += (long long)a[j];
        ans = max(ans,res);
    }
    printf("%lld\n",ans);
    return 0;
}