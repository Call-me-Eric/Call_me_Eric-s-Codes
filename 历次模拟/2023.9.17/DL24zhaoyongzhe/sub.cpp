#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 410, mod = 1e9 + 7;
int n, st;
char ch[maxn];
map<int,int> dp[51];
int dfs(int step,int sta){
    // printf("%lld %lld\n",step,sta);
    if(!step || step == 1){return dp[step][sta] = 1;}
    if(dp[step][sta])return dp[step][sta];
    int res = dfs(step - 1,sta & ((1 << step) - 1));
    for(int i = step - 1;i > 0;i--){
        if(((sta >> (i)) & 1) != ((sta >> (i + 1)) & 1)){
            res = (res + dfs(step - 1,(sta & ((1 << i) - 1)) | ((sta >> (i + 1)) << i))) % mod;
        }
    }
    return dp[step][sta] = res;
}
signed main(){
    freopen("sub.in","r",stdin);
    freopen("sub.out","w",stdout);
    scanf("%lld",&n);
    scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++){
        st |= (ch[i] - '0') << (n - i + 1);
    }
    printf("%lld\n",dfs(n,st));
    return 0;
}