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
const int maxn = 6e6 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, c;
int a[maxn], fa[maxn], b[maxn];
int id[maxn], r[maxn];
vector<int> vec[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void solve(){
    n = read(); c = read();int m = 0;
    for(int i = 1;i <= n;i++){b[i] = read();fa[i] = i;}
    a[m] = -114514;a[++m] = -1;
    for(int i = 1;i <= n;i++){a[++m] = b[i];id[m] = i;a[++m] = -1;}
    a[m + 1] = -191981;
    int R = 0, mid = 0;
    for(int i = 1;i <= m;i++){
        if(i < R){r[i] = min(R - i + 1,r[2 * mid - i]);}
        while(i + r[i] <= m && i - r[i] > 0 && a[i + r[i]] == a[i - r[i]]){
            fa[getf(id[i + r[i]])] = getf(id[i - r[i]]);
            r[i]++;
        }
        if(id[i + r[i]] && id[i - r[i]])vec[id[i + r[i]]].push_back(id[i - r[i]]);
        if(i + r[i] - 1 > R){R = i + r[i] - 1;mid = i;}
    }
    int ans = 1;
    for(int i = 1;i <= n;i++){
        if(getf(i) != i)continue;
        set<int> st;
        for(int v : vec[i])st.insert(getf(v));
        ans = (ans * (c - st.size())) % mod;
    }
    for(int i = 1;i <= m;i++){a[i] = 0;vec[i].clear();r[i] = 0;}
    printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("palindrome.in","r",stdin);
    freopen("palindrome.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}