#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, S;
const int maxn = 2e5 + 10;
int a[maxn];
int findd(int x){
    int l = x + 1, r = n;
    while(l < r){
        int mid = (l + r) >> 1;
        if(a[mid] + a[x] > S)r = mid;
        else l = mid + 1;
    }
    return l;
}
signed main(){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
    n = read(); S = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
    }
    sort(a + 1, a + 1 + n);
    int ans = 0;
    for(int i = 1; i <= n;i++){
        int pos = findd(i);
        if(pos <= n && pos > i && a[pos] + a[i] > S){ans += n - pos + 1;}
    }
    printf("%lld\n",ans);
    return 0;
}