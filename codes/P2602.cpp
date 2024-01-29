#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 20;
int f[maxn + 1][maxn + 1][2][2];
//f[i][j][k][l] -> i=从左向右第i位; j=目前有j位是目标数字;k=前i位与限制相同;l=前i位是0
int l, r;
int tmp[maxn + 1],tot;

int dfs(int x,int sum,bool up,bool zero, int d){
    if(f[x][sum][up][zero] != -1)return f[x][sum][up][zero];
    if(x == 0)return f[x][sum][up][zero] = sum;
    f[x][sum][up][zero] = 0;
    for(int i = 0;i < 10;i++){
        if(!up && i > tmp[x])break;
        f[x][sum][up][zero] += dfs(x - 1,sum + ((!zero || i) && (i == d)),up || (i < tmp[x]),(i == 0) && zero,d);
    }
    return f[x][sum][up][zero];
}
int dp(int x,int d){
    int t = x;tot = 0;
    memset(f,-1,sizeof(f));
    while(x){tmp[++tot] = x % 10;x /= 10;}
    return dfs(tot,0,0,1,d);
}

signed main(){
    scanf("%lld%lld",&l,&r);
    for(int i = 0;i < 10;i++){
        printf("%lld ",dp(r,i) - dp(l - 1,i));
    }
    puts("");
    return 0;
}