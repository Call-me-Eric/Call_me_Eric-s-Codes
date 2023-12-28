#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, d, k;
const int maxn = 5e5 + 10, maxd = 2e3 + 10,maxk = 1e9, inf = 0x8080808080808080;
struct node{
    int pos, point;
}a[maxn];
int dp[maxn];
bool check(int mid){
    int maxx = inf;
    deque<int> que;
    memset(dp,inf,sizeof(dp));
    que.push_back(0);//设一个原点0(point = 0, pos = 0)
    dp[0] = 0;
    int j = 0, leftt = max(1LL,d - mid), rightt = d + mid;
	for(int i = 1;i <= n;i++) {
        while(a[i].pos - a[j].pos >= leftt && j < i){
            if(dp[j] != inf){
                while(!que.empty() && dp[que.back()] <= dp[j]) que.pop_back();
                que.push_back(j);
            }
            j++;
        }
        while(!que.empty() && a[i].pos - a[que.front()].pos > rightt) que.pop_front();
        if(!que.empty()) dp[i] = dp[que.front()] + a[i].point;
    }
    for(int i = 1;i <= n;i++){
        maxx = max(maxx,dp[i]);
    }
    return maxx >= k;
}
signed main(){
    int sum = 0;
    n = read(); d = read(); k = read();
    int l = 0, r = 0,mid = 0, ans = -1;
    for(int i = 1;i <= n;i++){
        a[i].pos = read(); a[i].point = read();
        if(a[i].point > 0LL){
            sum += a[i].point;
            r = max(r,a[i].pos);
        }
    }
    if(sum < k){puts("-1");return 0;}
    while(l <= r){
        mid = (l + r) >> 1;
        if(!check(mid))l = mid + 1;
        else r = mid - 1,ans = mid;
    }
    printf("%lld\n",ans);
    return 0;
}