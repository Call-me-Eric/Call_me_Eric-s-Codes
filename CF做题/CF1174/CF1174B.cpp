#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch <'0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a[maxn], n;
signed main(){
    n = read();bool odd = 1, even = 1;
    for(int i = 1;i <= n;i++){
        a[i] = read();
        if(a[i] & 1)odd = 0;
        if((a[i] & 1) == 0)even = 0;
    }
    if(odd || even){for(int i = 1;i <= n;i++)printf("%d ",a[i]);}
    else {sort(a + 1,a + 1 + n);for(int i = 1;i <= n;i++)printf("%d ",a[i]);}
    return 0;
}