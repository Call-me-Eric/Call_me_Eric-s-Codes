#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10, mod = 1e9 + 7;
int n;
int range_[maxn], pos[maxn];
int l[maxn], r[maxn];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){pos[i] = read(); range_[i] = read();l[i] = r[i] = i;}
    for(int i = 2;i <= n;i++){
        while(l[i] > 1 && pos[i] - pos[l[i] - 1] <= range_[i]){
            range_[i] = max(range_[i],range_[l[i] - 1] - (pos[i] - pos[l[i] - 1]));
            l[i] = l[l[i] - 1];
        }
    }
    for(int i = n - 1;i >= 1;i--){
        while(r[i] < n && pos[r[i] + 1] - pos[i] <= range_[i]){
            l[i] = min(l[i],l[r[i] + 1]);
            r[i] = r[r[i] + 1];
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)ans = (ans + (r[i] - l[i] + 1) * i) % mod;
    printf("%lld\n",ans);
    return 0;
}