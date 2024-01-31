#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e5 + 10;
int n, I;
int a[maxn], b[maxn];
int pre[maxn], suf[maxn];
int buc[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x;
        if(res >= n)return n;
        x = x  * x;a >>= 1;
        if(x >= n)x = n;
    }
    return res;
}
signed main(){
    n = read(); I = read() * 8;
    for(int i = 1;i <= n;i++){b[i] = a[i] = read();}
    sort(b + 1,b + 1 + n);
    int tot = unique(b + 1,b + 1 + n) - b - 1;
    for(int i = 1;i <= n;i++){a[i] = lower_bound(b + 1,b + 1 + tot,a[i]) - b;}
    for(int i = 1;i <= n;i++)buc[a[i]]++;
    for(int i = 1;i <= tot;i++)pre[i] = buc[i] + pre[i - 1];
    for(int i = tot;i;i--)suf[i] = buc[i] + suf[i + 1];
    int ans = n, k = qpow(2,I / n);
    if(k >= tot){puts("0");return 0;}
    for(int i = 1;i + k - 1 <= tot;i++) ans = min(ans,pre[i - 1] + suf[i + k]);
    printf("%lld\n",ans);

    // printf("tot = %lld, k = %lld\n",tot, k);
    return 0;
}