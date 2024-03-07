#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >='0'&&ch <='9'){x=(x<<3)+(x<<1)+ch-'0'; ch = getchar();}
    return x * f;
}
const int maxn = 6e3 + 10;
int n; bool book[maxn];
int r[maxn], root, dp[maxn][2];
vector<int> child[maxn];
void dfs(int u){
    dp[u][1] = r[u];
    for(auto i:child[u]){
        dfs(i);
        dp[u][0] += max(dp[i][0],dp[i][1]);
        dp[u][1] += dp[i][0];
    }
    return;
}
signed main(){
    n = read(); int l, k;
    for(int i = 1;i <= n;i++) r[i] = read();
    for(int i = 1;i < n;i++){
        l = read(); k = read();
        child[k].push_back(l);
        book[l] = 1;
    }
    for(int i = 1;i <= n;i++) if(!book[i]){root = i;break;}
    dfs(root);
    printf("%d\n",max(dp[root][0],dp[root][1]));
    return 0;
}