#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x =0  , f =1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
int a[maxn];
signed main(){
    n = read(); m = read();int opt, l, r, w;
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= m;i++){
        opt = read(); l = read(); r = read();
        if(opt == 2){
            int sum = 0;
            for(int j = l;j <= r;j++)sum += a[j];
            printf("%d\n",sum);
        }
        else{
            w = read();
            for(int j = l;j <= r;j++)if(a[j] % w == 0)a[j] /= w;
        }
    }
    return 0;
}