#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
string s;
const int maxn = 110, mod = 1e9 + 7;
int dp[maxn][10][3];
int a[maxn];
int T;
int dfs(int pos,int pre,int turn,bool limit,bool invalid){
    if(pos == -1) return invalid ? 0 : 1;
    if(!limit && dp[pos][pre][turn] != -1)
        return dp[pos][pre][turn];
    int up = limit ? a[pos] : 9;
    int ans = 0;
    for(int i = 0;i <= up;i++){
        if(turn == 1 && i < pre) continue;
        int x;
        if(i == pre) x = turn;
        else if(i > pre) x = 1;
        else x = 2;
        if(invalid) x = 0;
        ans = (ans + dfs(pos - 1,i,x,limit && i == a[pos],i == 0 && invalid)) % mod;
    }
    if(!limit) dp[pos][pre][turn] = ans;
    return ans;
}
int solve(string x){
    int pos = 0;
    for(int i = x.length() - 1;i >= 0;i--) a[pos++] = x[i] - '0';
    return dfs(pos - 1,0,0,true,true);
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    cin >> T;
    while(T--){
        cin >> s;
        memset(dp,-1,sizeof(dp));
        cout << solve(s) << '\n';
    }
    return 0;
}