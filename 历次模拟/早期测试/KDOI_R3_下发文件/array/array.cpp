#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n;
const int maxn = 5100;
int b[maxn], sum;
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){b[i] = read();sum += b[i];}
    if(n == 1){if(b[1] == 0)puts("1");else puts("0");return 0;}
    else if(n == 2){if(b[1] == b[2])puts("1");else puts("0");return 0;}
    else if(sum & 1){puts("0");return 0;}
    sort(b + 1,b + 1 + n);
    
    return 0;
}