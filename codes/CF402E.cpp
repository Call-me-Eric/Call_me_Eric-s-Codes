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
const int maxn = 2000 + 10;
int n;
int a[maxn][maxn];
bitset<maxn> b[maxn];
void main(){
    n = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++){
            a[i][j] = read();b[i][j] = (a[i][j] > 0);
        }
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            if(b[i][k])b[i] |= b[k];
    for(int i = 1;i <= n;i++)
        if(b[i].count() != n){puts("NO");return;}
    puts("YES");
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