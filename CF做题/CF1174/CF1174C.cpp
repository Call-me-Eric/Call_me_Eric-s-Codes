#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch <'0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn], col;
int prime[maxn], tot;
int book[maxn];
signed main(){
    n = read();
    for(int i = 2;i <= n;i++){
        if(!book[i]){prime[++tot] = i;a[i] = ++col;}
        for(int j = 1;j <= tot && i * prime[j] <= n;j++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    for(int i = 1;i <= tot;i++){
        for(int j = 1;j * prime[i] <= n;j++){
            a[j * prime[i]] = a[prime[i]];
        }
    }
    for(int i = 2;i <= n;i++)printf("%d ",a[i]);
    return 0;
}