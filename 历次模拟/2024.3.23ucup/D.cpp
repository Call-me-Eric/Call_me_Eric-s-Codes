#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n;
vector<int> fac;
void main(){
    n = read();
    for(int i = 1;i * i <= n;i++){
        if(n % i == 0){fac.push_back(i);if(i * i != n)fac.push_back(n / i);}
    }
    if(fac.size() == 2 || fac.size() == 4){puts("Y");return;}
    if(fac.size() & 1){puts("N");return;}
    for(int i : fac)printf("%lld ",i);
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