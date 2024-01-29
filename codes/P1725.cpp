#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;  ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, l, r;
const int maxn = 2e5 + 10;
int dp[maxn], a[maxn];
deque<int> que;
signed main(){
    memset(dp,-0x3f,sizeof(dp));
    n = read(); l = read(); r = read();
    for(int i = 0;i <= n;i++){a[i] = read();}
    dp[0] = 0;
    for(int i = l;i <= n;i++){
        while(!que.empty() && dp[i - l] > dp[que.front()])que.pop_front();
        que.push_front(i - l);
        while(!que.empty() && que.back() < i - r)que.pop_back();
        dp[i] = dp[que.back()] + a[i];
    }
    int ans = -0x3f3f3f3f;
    for(int i = n - r + 1;i <= n;i++){
        ans = max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}