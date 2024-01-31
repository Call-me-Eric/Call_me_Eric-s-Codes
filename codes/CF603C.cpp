#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, k;
int SG(int x){
    if(x <= 1)return x;
    if(k % 2 == 1){
        if(x <= 4)return x - 2;
        if(x & 1)return 0;
        return SG(x / 2) != 1 ? 1 : 2;
    }
    if(x == 2)return x;
    return x % 2 == 0;
}
signed main(){
    n = read(); k = read();int ans = 0;
    for(int i = 1;i <= n;i++)ans ^= SG(read());
    puts(ans ? "Kevin" : "Nicky");
    return 0;
}