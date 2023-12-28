#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e6 + 10;
int fa[maxn], tot[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
signed main(){
    n = read(); m = read();
    int l, r, ans = 0;
    for(int i = 0;i <= n + 1;i++){fa[i] = i;}
    for(int i = 1;i <= m;i++){
        l = read(); r = read();
        r = getf(fa[r]);
        while(l <= r){
            if(l != r && getf(l) == r)break;
            fa[r] = getf(fa[r - 1]);
            ans++;
            r = getf(r);
        }
        printf("%d\n",n - ans);
    }
    return 0;
}
