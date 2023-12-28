#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 100100, maxm = 110;
int f[maxn], tot, cost[maxn], val[maxn];
signed main(){
    n = read(); m = read();
    int a, b, w;
    for(int i = 1;i <= n;i++){
        a = read(); b = read(); w = read();
        int j = 1;
        while(j <= a){
            cost[++tot] = j * w;
            val[tot] = j * b;
            a -= j; j *= 2;
        }
        if(a){cost[++tot] = a * w;val[tot] = b * a;}
    }
    for(int i = 1;i <= tot;i++){
        for(int j = m;j >= cost[i];j--){
            f[j] = max(f[j],f[j - cost[i]] + val[i]);
        }
    }
    printf("%lld\n",f[m]);
    return 0;
}