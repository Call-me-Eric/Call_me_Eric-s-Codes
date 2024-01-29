#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1100, mod = 1e9 + 7;
char s[2][maxn];
int tmp[maxn][2];
int ans[2], res[2];
int f[maxn][21][21][2];
int dfs(int x,int pre1,int pre2,bool suit,bool up,bool zero,int opt){
    if(!x)return suit;
    if(!up && !zero && pre1 != 10 && pre2 != 10
    && f[x][pre1][pre2][suit] != -1)return f[x][pre1][pre2][suit];
    int sum = 0, lmt = up ? tmp[x][opt] : 9;
    for(int i = 0;i <= lmt;i++){
        sum = (sum + dfs(x - 1, (zero && !i) ? 10 : i, (zero) ? 10 : pre1,
        suit || (!zero && (i == pre1)) || (!zero && (i == pre2)),
        up && (i == lmt),zero && !i,opt) % mod) % mod;
    }
    if(!zero && !up && pre1 != 10 && pre2 != 10)f[x][pre1][pre2][suit] = sum;
    return sum;
}
int solve(int opt,int add){
    memset(f,-1,sizeof(f));
    int len = strlen(s[opt] + 1);
    for(int i = 1;i <= len;i++){
        tmp[len - i + 1][opt] = s[opt][i] - '0';
    }
    int tot = 1;
    while(tmp[tot][opt] - add < 0){
        if(tot == len)break;
        tmp[tot][opt] = 9;
        tot++;
    }
    tmp[tot][opt] -= add;
    return dfs(len,10,10,0,1,1,opt) % mod;
}
signed main(){
    scanf("%s",s[0] + 1);
    scanf("%s",s[1] + 1);
    
    for(int i = 0;i < 2;i++){
        ans[i] = solve(i,!i) % mod;
    }
    printf("%lld\n",(ans[1] - ans[0] + mod) % mod);
    return 0;
}