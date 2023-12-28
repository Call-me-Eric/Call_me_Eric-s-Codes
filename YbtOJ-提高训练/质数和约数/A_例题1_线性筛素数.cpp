#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, q;
const int maxn = 1e8 + 10;
int prime[maxn], tot;
bool book[maxn];
signed main(){
    n = read(); q = read();
    for(int i = 2;i <= n;i++){
        if(!book[i]){prime[++tot] = i;}
        for(int j = 1;j <= tot && prime[j] * i <= n;j++){
            book[prime[j] * i] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    while(q--)printf("%d\n",prime[read()]);
    return 0;
}
