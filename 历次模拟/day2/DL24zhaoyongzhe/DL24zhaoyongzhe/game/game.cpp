#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn];
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
int T = read();
while(T--){
    n = read();for(int i = 1;i <= n;i++)a[i] = read();
    if(n & 1)puts("First");else puts("Draw");
}
    return 0;
}