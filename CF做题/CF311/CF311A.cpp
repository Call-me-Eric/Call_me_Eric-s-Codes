#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2100;
int n, k;
signed main(){
    n = read(); k = read();
    if(n * (n - 1) / 2 <= k)puts("no solution");
    else for(int i = 1;i <= n;i++){printf("0 %d\n",i);}
    return 0;
}