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
const int maxn = 2e4 + 10;
int n, x;
int a[maxn];
namespace Subtask1{

    void main(){
    }
};
void main(){
    n = read(); x = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    sort(a + 1,a + 1 + n);
    printf("%d\n",a[n]);
    return;
}
};
bool edmemory;
signed main(){
    freopen("message.in","r",stdin);
    freopen("message.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}