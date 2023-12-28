#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch  < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int n, k;
int p[maxn], q[maxn];
signed main(){
    freopen("strawberry.in","r",stdin);
    freopen("strawberry.out","w",stdout);
    n = read(); k = read();
    bool all1 = true;
    for(int i = 1;i < n;i++){
        p[i] = read(); q[i] = read();
        if(p[i] != 1 || q[i] != 1)all1 = false;
    }
    if(all1){
        if(n / 2 > k)printf("%d\n",n / 2 + 1);
        else printf("%d\n",k);
    }
    return 0;
}