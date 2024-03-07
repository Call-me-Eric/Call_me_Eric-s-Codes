#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10,mod = 1e9 + 7;
struct node{int a, b;}a[maxn];
int n, m, S = 1;
int t[maxn];
signed main(){
    n = read(); int u, v;
    for(int i = 1;i <= n;i++)t[i] = read();
    for(int i = 1;i <= n;i++){
        v = read();
        if(t[i] == 1)S += v;
        else a[++m] = node{t[i],v};
    }
    int id = 0; long double maxx = S;
    for(int i = 1;i <= m;i++){
        long double tmp = (S + a[i].b) * 1.0 / a[i].a;
        if(tmp > maxx){maxx = tmp;id = i;}
    }
    S %= mod;
    if(id)S = (S + a[id].b) % mod;
    for(int i = 1;i <= m;i++)if(i != id)S = (S * a[i].a) % mod;
    printf("%lld\n",S);
    return 0;
}