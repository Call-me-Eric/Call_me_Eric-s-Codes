#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxsq = 450;
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
int n;
int g[maxn], h[maxn];
bitset<maxn> st;
void main(){
    n = read();if(n == 1){puts("N");return;}
    int sum = 0;
    for(int i = 1;i <= n;i++){sum += (g[i] = read()); h[i] = read();}
    int gd = h[1];
    for(int i = 2;i <= n;i++)gd = gcd(gd,h[i]);
    sort(g + 1,g + 1 + n);int srt = sqrt(sum);
    
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