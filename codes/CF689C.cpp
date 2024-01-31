#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
int check(int mid){
    int cnt = 0;
    for(int i = 2;i * i * i <= mid;i++)
        cnt += mid / i / i / i;
    return cnt;
}
signed main(){
    n = read();
    int l = 1, r = 1e18 + 1, ans = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid) >= n){ans = mid;r = mid - 1;}
        else l = mid + 1;
    }
    if(ans == -1 || check(ans) != n)puts("-1");
    else printf("%lld\n",ans);
    return 0;
}