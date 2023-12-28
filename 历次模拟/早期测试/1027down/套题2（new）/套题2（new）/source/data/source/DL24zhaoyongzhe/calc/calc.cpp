#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, k;
const int maxk = 1100,maxn = 1e9 + 10;
int a[maxk];
bool book[maxn];
signed main(){
    freopen("calc.in","r",stdin);
    freopen("calc.out","w",stdout);
    n  =read(); k = read();
    for(int i = 1;i <= k;i++){
        a[i] = read();
    }
    int cnt = 0;
    sort(a + 1,a + 1 + k);
    for(int i = 1;i <= k;i++){
        for(int j = 1;j * a[i] <= n;j++){
            if(!book[j * a[i]])cnt++;
            book[j * a[i]] = 1;
        }
    }
    printf("%lld\n",n - cnt);
    return 0;
}