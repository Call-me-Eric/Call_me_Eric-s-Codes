#include<bits/stdc++.h>
#define lowbit(x) (x) & (-(x))
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, ans, tot;
const int maxn = 5e5 + 10;
int a[maxn], c[maxn * 4], p[maxn];
void update(int x,int y){for(;x <= tot;x += lowbit(x))c[x] += y;}
int sum(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
int sum(int x,int y){return sum(y) - sum(x);}
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        p[i] = a[i] = read();
    }
    sort(p + 1,p + 1 + n);
    tot = unique(p + 1,p + 1 + n) - p - 1;
    for(int i = 1;i <= n;i++){
        a[i] = lower_bound(p + 1,p + 1 + tot,a[i]) - p;
    }
    for(int i = 1;i <= n;i++){
        update(a[i],1);
        ans += sum(a[i],tot);
    }
    printf("%d\n",ans);
    return 0;
}
