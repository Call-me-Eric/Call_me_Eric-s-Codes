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
const int maxn = 3e5 + 10;
int n, C, a[maxn];
void main(){
    n = read(); C = read();int mx = 0, now = 0, sum = 0, mn = 0, now1 = 0;
    for(int i = 1;i <= n;i++){
        a[i] = read();sum += a[i];
        if(now + a[i] < 0){now = 0;}
        else now += a[i];
        if(now1 + a[i] > 0)now1 = 0;
        else now1 += a[i];
        mx = max(mx,now);mn = min(mn,now1);
    }
    if(C == 0){printf("%lld\n",sum - mn);}
    else if(C > 0) printf("%lld\n",sum + (C - 1) * mx);
    else{printf("%lld\n",sum + (C - 1) * mn);}
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