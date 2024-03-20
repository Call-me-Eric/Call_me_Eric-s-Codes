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
const int maxn = 3e5 + 10;
int n, p;
int a[maxn], tmp[maxn];
bool check(int q){
    for(int i = 0;i < n;i++)if(a[i] != a[(i + q) % n])return false;
    return true;
}
void update(int q){
    for(int i = 0;i < n;i++)tmp[i] = (a[i] - a[(i + q) % n] + p) % p;
    for(int i = 0;i < n;i++)a[i] = tmp[i];
}
void main(){
    n = read(); p = read();
    for(int i = 0;i < n;i++)a[i] = read() % p;
    int t = 1;
    while(n % (t * p) == 0)t = t * p;
    if(!check(t)){puts("-1");return;}
    int ans = 0;n = t;
    while(n > 1){t = n / p;while(!check(t)){ans += t;update(t);}n = t;}
    printf("%d\n",ans + (a[0] != 0));
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