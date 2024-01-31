#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2000 + 10;
int n, a[maxn];
int gcd(int x ,int y){return y == 0 ? x : gcd(y,x % y);}
signed main(){
    n = read();int cnt = 0;
    for(int i = 1;i <= n;i++){
        a[i] = read();
        cnt += (a[i] == 1);
    }
    if(cnt){printf("%d\n",n - cnt);return 0;}
    int minn = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){
        int x = a[i];
        for(int j = 1 + i;j <= n;j++){
            x = gcd(x, a[j]);
            if(x == 1){minn = min(minn,j - i);break;}
        }
    }
    if(minn == 0x3f3f3f3f)puts("-1");
    else printf("%d\n",n + minn - 1);
    return 0;
}