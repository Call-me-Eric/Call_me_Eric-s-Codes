#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
typedef long long ll;
const int maxn = 3e5 + 10;
priority_queue<ll> que;
int n;
signed main(){
    n = read();ll u, ans = 0;
    for(int i = 1;i <= n;i++){
        u = read();que.push(-u);//这个-u指的是买入股票花费
        if(que.empty() || que.top() + u < 0)continue;
        ans += u + que.top();que.pop();que.push(-u);
        //这个-u指的是，更改一个股票的卖出时间，原来的卖出收益就没了，需要减去
    }
    printf("%lld\n",ans);
    return 0;
}