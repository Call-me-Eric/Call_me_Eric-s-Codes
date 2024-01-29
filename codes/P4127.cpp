#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 30;
int l, r;int tmp[maxn], tot, mod;
int f[maxn][maxn * 10][maxn * 10];

int dfs(int x,int sum,int res,bool up){
    if(x > tot && (sum == 0))return 0;
    if(x > tot){return ((res == 0) && (sum == mod));}
    if(!up && (f[x][sum][res] != -1))return f[x][sum][res];
    int rest = 0;
    for(int i = 0;i <= 9;i++){
        if((i > tmp[tot - x + 1]) && up)break;
        rest += dfs(x + 1,sum + i,(10 * res + i) % mod,(i == tmp[tot - x + 1]) && up);
    }
    return up ? rest : f[x][sum][res] = rest;
}
int dp(int x){
    int ans = 0;tot = 0;
    while(x){tmp[++tot] = x % 10;x /= 10;}
    for(mod = 1;mod <= 9 * tot;mod++){
        memset(f,-1,sizeof(f));
        ans += dfs(1,0,0,1);
    }
    return ans;
}
signed main(){
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",dp(r) - dp(l - 1));
    return 0;
}