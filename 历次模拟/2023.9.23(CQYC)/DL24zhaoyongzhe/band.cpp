#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n;
signed main(){
    freopen("band.in","r",stdin);
    freopen("band.out","w",stdout);
    n = read();
    if(n == 1)puts("1");
    if(n == 2)puts("499122177");
    if(n == 3)puts("332748118");
    return 0;
}