#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
signed main(){
    freopen("test.in","r",stdin);
    int t = read();
    fclose(stdin);
    freopen("test.in","w",stdout);
    printf("%d\n",t + 1);
    return 0;
}