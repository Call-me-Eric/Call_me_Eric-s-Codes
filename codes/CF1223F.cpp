#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e6 + 10;
int n;
int a[maxn];
map<int,int> mp[maxn];
int nxt[maxn], f[maxn];
signed main(){
int T;scanf("%lld",&T);
while(T--){
    scanf("%lld",&n);
    for(int i = 1;i <= n;i++)scanf("%lld",&a[i]);
    for(int i = 1;i <= n;i++){mp[i].clear();f[i] = nxt[i] = 0;}
    for(int i = 1;i <= n;i++){
        if(mp[i - 1].count(a[i])){
            int p = mp[i - 1][a[i]];
            nxt[i] = p;
            swap(mp[i],mp[p - 1]);
            if(p != 1)mp[i][a[p - 1]] = p - 1;
        }
        mp[i][a[i]] = i;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(!nxt[i])continue;
        f[i] = f[nxt[i] - 1] + 1;
        ans += f[i];
    }
    printf("%lld\n",ans);
}
    return 0;
}