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
const int maxn = 1e5 + 10;
bool check(int x,int y){
    int l = 1, r = 1;
    while(l <= x)l *= 10;while(r <= y)r *= 10;
    while(r != 1){
        l /= 10;r /= 10;
        if((x / l != y / r))return false;
        x %= l;y %= r;
    }
    return true;
}
int BF(int n){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(check(i,sqrt(i)))cnt++;
    }
    return cnt;
}
int solve(int n){
    int ans = 0;
    if(n >= 1)ans++;
    for(int i = 10;(i - 2) * (i - 2) <= n;i *= 10){
        if((i - 2) * (i - 2) <= n){
            if((i - 2) * i <= n) ans++;
            if((i - 1) * i <= n){
                ans += (min(n,i * i - 1) - (i - 1) * i + 1);
                if(i * i <= n){
                    ans += min(n,i * i + (i - 1)) - i * i + 1;
                }
            }
        }
    }
    printf("%lld\n",ans);
    return ans;
}
void main(){int T = read();while(T--){solve(read());}return;}
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