#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n;
const int maxn = 17;
int f[1 << maxn];
signed main(){
    n = read();
    for(int i = 1;i < (1 << n);i++){f[i] = read();}
    for(int i = 1;i < (1 << n);i++){
        for(int j = i;j;j = (j - 1) & i){
            f[i] = max(f[i],f[i - j] + f[j]);
        }
    }
    printf("%d\n",f[(1 << n) - 1]);
    return 0;
}