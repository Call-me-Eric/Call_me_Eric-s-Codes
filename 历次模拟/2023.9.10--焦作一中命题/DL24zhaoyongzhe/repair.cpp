#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10, mod = 1000003;
int n;
int a[maxn];
priority_queue<pair<int,int> > que;
signed main(){
    freopen("repair.in","r",stdin);
    freopen("repair.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){a[i] = read();que.push(make_pair(a[i],i));}
    int ans = 0;
    int mi = n + 1, mx = 0;
    while(!que.empty()){
        int val = que.top().first;
        while(que.top().first == val){mi = min(mi,que.top().second);mx = max(mx,que.top().second);que.pop();}
        int lt = a[mi - 1], rt = a[mx + 1];
        if(mi == 1 || mx == n)break;
        if(rt > lt){
            ans = (ans + (rt + lt + a[mx]) * (lt - a[mx]) + (lt - a[mx]) * (lt - a[mx]) / 2) % mod;
            a[mx] = lt;
        }
        else {
            ans = (ans + (rt + lt + a[mx]) * (rt - a[mx]) + (rt - a[mx]) * (rt - a[mx]) / 2) % mod;
            a[mx] = rt;
        }
        ans = (ans + (mx - mi) * (a[mx] + a[mx] + a[mi]) % mod + (a[mx] - a[mi]) * (a[mx] - a[mi] + 1) / 2 % mod) % mod;
    }
    printf("%lld\n",ans % mod);
    return 0;
}