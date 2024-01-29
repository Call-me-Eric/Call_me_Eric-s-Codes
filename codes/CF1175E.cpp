#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;

int n, m;
int st[22][maxn];

signed main(){
    n = read(); m = read(); int u, v, mx = 0;
    for(int i = 1;i <= n;i++){
        u = read(); v = read();
        st[0][u] = max(st[0][u], v);
        mx = max(mx, v);
    }
    
    for(int i = 1;i <= mx;i++)st[0][i] = max(st[0][i], st[0][i - 1]);

    for(int k = 1;k <= 21;k++)
        for(int i = 0;i <= mx;i++){
            st[k][i] = st[k - 1][st[k - 1][i]];
        }
    
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        int ans = 0;
        for(int k = 21;k + 1;k--)
            if(st[k][u] < v){
                u = st[k][u];
                ans += (1 << k);
            }
        if(st[0][u] < v)puts("-1");
        else printf("%d\n",ans + 1);
    }
    return 0;
}