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
const int maxn = 2e5 + 10;
int n, x;
int p[maxn], deg[maxn], book[maxn];
void solve(){
    n = read(); x = read();
    for(int i = 1;i <= n;i++){deg[i] = book[i] = 0;}
    for(int i = 1;i < n;i++){deg[read()]++;deg[read()]++;}
    for(int i = 1;i <= n;i++){p[i] = read();}
    bool flag = true;int R = -1;
    for(int i = 1;i <= n;i++){if(deg[i] == n - 1)R = i;flag &= (p[i] == i);}
    if(flag || R == -1){puts("Alice");return;}
    if(x == R && p[x] != x){puts("Bob");return;}
    if(p[R] != R && x == p[R]){puts("Bob");return;}
    int sum = n;
    for(int i = 1;i <= n;i++)
        if(!book[i]){for(int j = i;!book[j];book[j] = 1,j = p[j]);sum--;}
    if(sum == 1){
        for(int i = 1;i <= n;i++)
            if(p[i] != i && i != x && p[i] != x){puts("Alice");return;}
    }
    sum += (x != R);
    puts((sum & 1) ? "Alice" : "Bob");
}
void main(){int T = read();while(T--)solve();return;}
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