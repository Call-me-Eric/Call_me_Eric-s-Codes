#include <bits/stdc++.h>
#define ll long long
#define rep(a,b,c)  for(int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
ll n, k;
signed main(){
    n = 2e5;k = 1000000000000000000;
    freopen("CF837F.in","w",stdout);
    printf("%lld %lld\n",n,k);
    for(int i = 1;i <= n - 2;i++){putchar('0');putchar(' ');}
    printf("1 1\n");
    return 0;
}