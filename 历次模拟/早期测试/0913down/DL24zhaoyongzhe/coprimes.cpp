#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1e5 + 10;
int p[maxn],tot;
bool book[maxn];
signed main(){
    freopen("coprimes.in","r",stdin);
    freopen("coprimes.out","w",stdout);
    n = read();
    int ans = n;
    for(int i = 2;i * i <= n;i++){
        if(!book[i]){p[++tot] = i;}
        for(int j = 1;j <= tot && p[j] * i <= n;j++){
            book[i * p[j]] = 1;
            if(i % p[j] == 0)break;
        }
    }
    for(int i = 1;i <= tot && p[i] * p[i] <= n;i++){
        if(n % p[i] == 0){
            ans = ans - ans / p[i];
            while(n % p[i] == 0)n /= p[i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}