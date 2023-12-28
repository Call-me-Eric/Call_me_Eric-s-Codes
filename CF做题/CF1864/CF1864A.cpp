#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
int x, y, n;
int a[maxn];
signed main(){
int T = read();
while(T--){
    x = read();y = read();n = read();
    a[n] = y;bool flag = true;
    for(int i = 1;i < n;i++){
        a[n - i] = a[n - i + 1] - i;
        // printf("i = %d, dec = %d\n",i,dec);
        if(a[n - i] < x){flag = false;break;}
    }
    if(!flag){puts("-1");}
    else{
        a[1] = x;
        for(int i = 1;i <= n;i++)printf("%d ",a[i]);
        puts("");
    }
}
    return 0;
}