#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10;
int a[maxn][8];
int n, m;int f[1 << 8];
int x,  y;
bool check(int mid){
    memset(f,0,sizeof(f));
    for(int i = 1;i <= n;i++){
        int sta = 0;
        for(int j = 0;j < m;j++)
            if(a[i][j] >= mid)sta |= (1 << j);
        if(sta == (1 << m) - 1){x = y = i;return true;}
        for(int sta1 = sta;sta1;sta1 = sta & (sta1 - 1))
            if(f[sta1]){x = f[sta1];y = i;return true;}
        f[((1 << m) - 1) ^ sta] = i;
    }
    // printf("mid = %d\n",mid);
    // for(int i = 0;i < (1 << m);i++)printf("sta = %d,f = %d\n",i,f[i]);
    return false;
}
signed main(){
    n = read(); m = read(); int mx = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 0;j < m;j++)
            mx = max(mx,a[i][j] = read());
    int l = 0, r = mx, ans = 0;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)){l = mid + 1;ans = mid;}
        else r = mid - 1;
    }
    check(ans);
    printf("%d %d\n",x, y);
    return 0;
}