#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int k, n, m,a[maxn], b[maxn], c[maxn], l[maxn], r[maxn];
bool check(int mid){
    int suml = 0, sumr = 0;
    for(int i = 1;i <= k;i++){
        l[i] = ceil(1.0 * (a[i] * m - mid) / n);
        r[i] = (a[i] * m + mid) / n;
        if(l[i] < 0)l[i] = 0; c[i] = 0;
        suml += l[i];sumr += r[i];
    }
    int rest = m - suml;
    // printf("rest = %lld,",rest);
    // printf("mid = %lld\n",mid);
    // for(int i  = 1;i <= k;i++){printf("l[%lld]=%lld r[%lld]=%lld\n",i,l[i],i,r[i]);}
    if(!(suml <= m && m <= sumr))return false;
    for(int i = 1;i <= k;i++){
        c[i] = l[i] + min(r[i] - l[i],rest);
        rest -= (c[i] - l[i]);
    }
    return rest == 0;
}
signed main(){
    k = read(); n = read(); m = read();
    for(int i = 1;i <= k;i++){a[i] = read();}
    int L = 0, R = 1e9, mid = 0;
    while(L <= R){
        mid = L + R >> 1;
        if(check(mid)){
            for(int i = 1;i <= k;i++)b[i] = c[i];
            // printf("mid = %lld\n",mid);
            R = mid - 1;
        }
        else L = mid + 1;
    }
    // check(60);
    for(int i = 1;i <= k;i++)printf("%lld ",b[i]);
    return 0;
}