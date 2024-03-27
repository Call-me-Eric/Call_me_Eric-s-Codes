#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
const int mod = 10007;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = ((x << 1) + (x << 3) + (ch ^ 48)) % mod;ch = getchar();}
    return x * f;
}
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void main(){
    int n = read();printf("%d\n",(n + 2) % mod * (n + 1) % mod * (n) % mod * 1668 % mod);
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}