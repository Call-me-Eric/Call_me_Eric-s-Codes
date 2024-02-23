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
int n, m;
int a[maxn], b[maxn];
int s[maxn], t[maxn];
int p[maxn], q[maxn];
vector<pair<int,int> > f[maxn];
map<int,int> dp;
void main(){
    n = read(); m = read();int ans = 0;
    for(int i = 1;i <= n;i++){a[i] = read() + a[i - 1]; s[i] = read(); p[i] = read();}
    for(int i = 1;i <= m;i++){b[i] = read() + b[i - 1]; t[i] = read(); q[i] = read();}
    for(int i = 1;i <= n;i++){
        if(a[i] <= s[i]){
            int j = upper_bound(b + 1,b + 1 + m,s[i] - a[i]) - b;
            ans += p[i];
            if(j <= m){f[i].push_back(make_pair(j,-p[i]));}
        }
    }
    for(int j = 1;j <= m;j++){
        if(b[j] <= t[j]){
            int i = upper_bound(a + 1,a + 1 + n,t[j] - b[j]) - a;
            if(i <= n){f[i].push_back(make_pair(j,q[j]));}
            else ans += q[j];
        }
    }
    dp[m + 1] = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1;i <= n;i++){
        sort(f[i].begin(),f[i].end(),[&](auto x,auto y){return x.second > y.second;});
        for(auto j : f[i]){
            int val = j.second,id = j.first;
            for(auto it = dp.lower_bound(id);val < 0;it = dp.erase(it)){
                id = it->first;val += it->second;
            }
            dp[id] += val;
        }
    }
    for(auto i : dp){if(i.first <= m)ans += i.second;}
    printf("%lld\n",ans);
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