#include<bits/stdc++.h>
#define lowbit(x) (x) & (-(x))
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, q;
const int maxn = 1e6 + 10;
int a[maxn], c[maxn * 4];
void update(int x,int y){for(;x <= n;x += lowbit(x))c[x] += y;}
int sum(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
int sum(int x,int y){return sum(y) - sum(x - 1);}
signed main(){
    n = read(); q = read();int op, x, y;
    for(int i = 1;i <= n;i++){a[i] = read();update(i,a[i]);}
    for(int i = 1;i <= q;i++){
        op = read(); x = read(); y = read();
        if(op == 2)
            printf("%d\n",sum(x,y));
        else update(x,y);
    }
    return 0;
}
