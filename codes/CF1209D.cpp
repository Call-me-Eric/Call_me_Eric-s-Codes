#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, k;

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

signed main(){
    n = read(); k = read();int u, v, cnt = 0;
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= k;i++){
        u = read(); v = read();
        int fu = getf(u), fv = getf(v);
        if(fu != fv){fa[fu] = fv;}
    }
    for(int i = 1;i <= n;i++){cnt += (fa[i] == i);}
    printf("%d\n",k - n + cnt);
    return 0;
}