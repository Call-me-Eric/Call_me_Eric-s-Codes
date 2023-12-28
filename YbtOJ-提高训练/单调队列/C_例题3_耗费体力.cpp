#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1000010;
int dp[maxn], a[maxn];
int DP(int k){
    deque<int> que;
    memset(dp,0x3f,sizeof(dp));
    dp[1] = 0;
    que.push_back(1);
    for(int i = 2;i <= n;i++){
        while(!que.empty() && i - que.front() > k)que.pop_front();
        if(a[que.front()] > a[i])dp[i] = dp[que.front()];
        else dp[i] = dp[que.front()] + 1;
        while(!que.empty() && (dp[que.back()] > dp[i] || dp[que.back()] == dp[i] && a[que.back()] <= a[i]))que.pop_back();
        que.push_back(i);
    }
    return dp[n];
}
signed main(){
    n = read(); for(int i = 1;i <= n;i++) a[i] = read();
    m = read(); for(int i = 1;i <= m;i++) printf("%d\n",DP(read()));
    return 0;
}