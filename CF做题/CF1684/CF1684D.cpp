#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, k;int a[maxn];
priority_queue<int,vector<int>,less<int> > que;
signed main(){
int T = read();
while(T--){
    n = read(); k = read();
    while(!que.empty())que.pop();
    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans += (a[i] = read());
        que.push(a[i] - (n - i));
    }
    for(int i = 1;i <= k;i++){ans -= que.top();que.pop();}
    printf("%lld\n",ans - k * (k - 1) / 2);
}
    return 0;
}