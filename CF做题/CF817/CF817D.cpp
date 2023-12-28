#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int a[maxn], n;
int L[maxn], R[maxn];
int l[maxn], r[maxn];
int ans;
stack<pair<int,int> > stk;
signed main(){
    n = read();for(int i = 1;i <= n;i++)a[i] = read();

    a[0] = a[n + 1] = 0x3f3f3f3f3f3f3f3f;
    while(!stk.empty())stk.pop();stk.push(make_pair(a[0],0));
    for(int i = 1;i <= n;i++){
        while(!stk.empty() && stk.top().first < a[i])stk.pop();
        L[i] = stk.top().second + 1;
        stk.push(make_pair(a[i],i));
    }
    while(!stk.empty())stk.pop();stk.push(make_pair(a[n + 1],n + 1));
    for(int i = n;i;i--){
        while(!stk.empty() && stk.top().first <= a[i])stk.pop();
        R[i] = stk.top().second - 1;
        stk.push(make_pair(a[i],i));
    }
    
    for(int i = 1;i <= n;i++){l[i] = L[i];r[i] = R[i];}
    // for(int i = 1;i <= n;i++){printf("i=%lld : L=%lld R=%lld\n",i,L[i],R[i]);}
    
    a[0] = a[n + 1] = -1;
    while(!stk.empty())stk.pop();stk.push(make_pair(a[0],0));
    for(int i = 1;i <= n;i++){
        while(!stk.empty() && stk.top().first > a[i])stk.pop();
        L[i] = stk.top().second + 1;
        stk.push(make_pair(a[i],i));
    }
    while(!stk.empty())stk.pop();stk.push(make_pair(a[n + 1],n + 1));
    for(int i = n;i;i--){
        while(!stk.empty() && stk.top().first >= a[i])stk.pop();
        R[i] = stk.top().second - 1;
        stk.push(make_pair(a[i],i));
    }

    for(int i = 1;i <= n;i++){
        ans += (a[i] * ((i - l[i] + 1) * (r[i] - i + 1) - (i - L[i] + 1) * (R[i] - i + 1)));
    }
    // for(int i = 1;i <= n;i++){printf("i=%lld : L=%lld R=%lld\n",i,L[i],R[i]);}
    
    printf("%lld\n",ans);
    return 0;
}