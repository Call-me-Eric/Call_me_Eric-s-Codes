#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f= 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, q;
int a[maxn];
int r[maxn], sum[maxn];
signed main(){
    n = read(); q = read();
    for(int i = 1;i <= n;i++){r[a[i] = read()] = i;sum[a[i]]++;}
    int i = 1, res = 0;
    while(i <= n){
        int mxr = i, mxsum = 0;
        while(i <= mxr){
            mxr = max(mxr,r[a[i]]);
            mxsum = max(mxsum,sum[a[i]]);
            i++;
        }
        res += mxsum;
    }
    printf("%d\n",n - res);
    return 0;
}