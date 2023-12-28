#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, a[maxn];
int buc[30];
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        a[i] = read();
        for(int j = 20;j + 1;j--)
            if(a[i] & (1 << j))buc[j]++;
        a[i] = 0;
    }
    long long sum = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 20;j + 1;j--)
            if(buc[j]){a[i] |= (1 << j);buc[j]--;}
        sum += (long long)a[i] * a[i];
    }
    printf("%lld\n",sum);
    return 0;
}