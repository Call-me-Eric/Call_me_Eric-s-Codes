#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int mod = 998244353;
int n, k;
signed main(){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
    n = read(); k = read();
    if(k == 2){puts("2");return 0;}
    
    return 0;
}