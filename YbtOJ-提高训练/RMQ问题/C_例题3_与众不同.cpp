#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' ||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 2e5 + 10, maxx = 1e6;
int last[maxx * 2], st[maxn];
int f[maxn][21], logg[maxn];
int query(int l,int r){
    if(l > r)return -1145141919;
    int lg = logg[r - l + 1];
    return max(f[l][lg],f[r - (1 << lg) + 1][lg]);
}
signed main(){
    n = read(); m = read();
    logg[0] = -1;int x;
    for(int i = 1;i <= n;i++){
        x = read();
        logg[i] = logg[i >> 1] + 1;
        st[i] = max(st[i - 1], last[x + maxx] + 1);
        f[i][0] = i - st[i] + 1;
        last[x + maxx] = i;
    }
    for(int j = 1;j <= 20;j++)
        for(int i = 1;i + (1 << j) - 1 <= n;i++)
            f[i][j] = max(f[i][j - 1],f[i + (1 << (j - 1))][j - 1]);
    for(int i = 1;i <= m;i++){
        int l = read() + 1, r = read() + 1;
        int tmp = lower_bound(st + l,st + r + 1,l) - (st + l);
        printf("%d\n",max(query(tmp + l + 1,r),tmp));
    }
    return 0;
}