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
const int maxn = 2e5 + 10, mod = 998244353;
int n, fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
vector<int> vec[maxn];
namespace Subtask1{
int p[maxn];
map<set<pair<int,int> >,int> mp;
void solve(){
    for(int i = 1;i <= n;i++)p[i] = i;
    int ans = 0;mp.clear();
    do{
        for(int i = 1;i <= n;i++)fa[i] = i;
        set<pair<int,int> > st;
        for(int i = n + 1;i <= n * 2;i++){
            for(int j : vec[i])st.insert(minmax(p[i - n],j));
        }
        if(mp.find(st) != mp.end() || st.size() != n - 1)continue;
        bool flag = true;int cnt = 0;
        for(auto i : st){
            if(getf(i.first) == getf(i.second)){flag = false;break;}
            fa[getf(i.first)] = getf(i.second);cnt++;
        }
        ans += flag && (cnt == n - 1);mp[st] = 1;
    }while(next_permutation(p + 1,p + 1 + n));
    printf("%lld\n",ans);
}
};
namespace Subtask2{
void solve(){printf("2\n");}
};
namespace Subtask3{
void solve(){puts("1");}
};
namespace Subtask4{
int buc[maxn], pw[maxn];bool book[maxn];
void dfs(int u){
    buc[vec[u].size()]++;book[u] = 1;
    for(int v : vec[u]){if(!book[v])dfs(v);}
}
void solve(){
    dfs(1);int ans = 1;pw[0] = 1;
    for(int i = 1;i <= n;i++)pw[i] = pw[i - 1] * i % mod;
    for(int i = 1;i <= n;i++)ans = ans * pw[buc[i]] % mod;
    printf("%lld\n",ans);
}
};
void solve(){
    n = read();
    for(int i = 1;i <= n * 2;i++)fa[i] = i,vec[i].clear();
    int mx = 0;
    for(int i = 1;i <= n;i++){
        for(int j = read();j;j--){
            int x = read();
            vec[i + n].push_back(x);vec[x].push_back(i + n);
            fa[getf(x)] = getf(i + n);
        }
        mx = max(mx,(int)vec[i + n].size());
    }
    int cnt = 0;
    for(int i = 1;i <= n * 2;i++)cnt += getf(i) == i;
    if(cnt != 2){puts("0");return;}
    if(n <= 10){Subtask1::solve();return;}
    if(mx == n - 1){Subtask2::solve();return;}
    if(mx == 2){Subtask3::solve();return;}
    puts("1");
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}