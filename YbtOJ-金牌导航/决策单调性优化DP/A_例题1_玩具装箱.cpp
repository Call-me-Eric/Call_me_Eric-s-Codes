#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, L;
int sum[maxn], f[maxn];

int stk[maxn], top, pos;
long double calcx(int x){return sum[x];}
long double calcy(int x){return f[x] + (sum[x] + L) * (sum[x] + L);}
long double slope(int x,int y){return (calcy(y) - calcy(x)) / (calcx(y) - calcx(x));}

signed main(){
    n = read(); L = read() + 1;stk[++top] = 0;pos = 1;
    for(int i = 1;i <= n;i++){sum[i] = read() + sum[i - 1] + 1;}
    for(int i = 1;i <= n;i++){
        while(pos < top && slope(stk[pos],stk[pos + 1]) <= 2ll * sum[i])pos++;
        f[i] = f[stk[pos]] + (sum[stk[pos]] - sum[i] + L) * (sum[stk[pos]] - sum[i] + L);
        while(top > pos && slope(stk[top - 1],stk[top]) >= slope(stk[top - 1],i))top--;stk[++top] = i;
    }
    printf("%lld\n",f[n]);
    return 0;
}