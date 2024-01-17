#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n, q;
int k, a[maxn];
int pos[maxn], p[maxn];
signed main(){
    freopen("permutation.in","r",stdin);
    freopen("permutation.out","w",stdout);
    n = read(); k = read(); q = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    if(k == 0){
        while(q--){
            int u = read(), v = read();
            if(u > 1)puts("-1");
            else printf("%lld\n",a[v]);
        }
    }
    if(k == 1){
        int posl = 1, posr = n;
        for(int i = 1;i < n;i++){
            if(a[i] < a[i + 1])pos[i] = posr--;
            else pos[i] = posl++;
            p[pos[i]] = i;
        }
        a[n + 1] = a[n];
        while(q--){
            int u = read(), v = read();
            if(u > n){puts("-1");continue;}
            if(p[u] != v && p[u] + 1 != v)printf("%lld\n",a[v]);
            else printf("%lld\n",a[v + (p[u] == v ? 1 : -1)]);
        }
    }
    return 0;
}