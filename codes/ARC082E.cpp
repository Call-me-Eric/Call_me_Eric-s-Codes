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
const int maxn = 2e2 + 10, mod = 998244353;
typedef pair<int,int> pii;

int n, pw[maxn];
pii p[maxn];
bool operator < (pii a,pii b){return a.first != b.first ? a.first < b.first : a.second < b.second;}

void main(){
    n = read();pw[0] = 1;
    for(int i = 1;i <= n;i++){
        int u = read(), v = read();
        p[i] = make_pair(u, v);
        pw[i] = pw[i - 1] * 2ll % mod;
    }
    sort(p + 1,p + 1 + n);int ans = pw[n];
    auto calc = [](int i,int j){
        if(p[i].first == p[j].first) return 1e18;
        return 1.0 * (p[j].second - p[i].second) / (p[j].first - p[i].first);
    };
    auto check = [&](int i,int k,int j){
        return calc(i,k) == calc(k,j);
    };
    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            int cnt = 0;
            for(int k = i + 1;k < j;k++)
                cnt += check(i,k,j);
            ans -= pw[cnt];if(ans < 0)ans += mod;
            // printf("(%lld,%lld) - (%lld,%lld), cnt = %lld\n",p[i].first,p[i].second,p[j].first,p[j].second,cnt);
        }
    }
    printf("%lld\n",(ans - n - 1 + mod) % mod);
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