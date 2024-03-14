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
const int maxn = 2e3 + 10;
int n;
vector<int> edg[maxn];
int c[maxn];
typedef pair<double,int> pdi;
pdi pr[maxn];
int fa[maxn], ans[maxn];
bool flag = true;
vector<pdi> dfs(int u){
    vector<pdi> vec;vec.clear();
    double mx = 0;
    pr[u] = make_pair(0,u);
    for(int v : edg[u]){
        auto tmp = dfs(v);
        if(!flag)return vec;
        double add = mx + n;
        for(auto i : tmp){
            pr[i.second].first += add;
            vec.push_back(pr[i.second]);
            mx = max(mx,pr[i.second].first);
        }
    }
    sort(vec.begin(),vec.end());
    if(vec.size() < c[u]){flag = false;return vec;}
    if(vec.size() == 0){pr[u].first = 1;}
    else{
        if(c[u] == 0)pr[u].first = vec[0].first - 10;
        else if(c[u] == vec.size())pr[u].first = vec.back().first + 10;
        else {pr[u].first = (vec[c[u] - 1].first + vec[c[u]].first) / 2.0;}
    }
    vec.push_back(pr[u]);return vec;
}
void main(){
    n = read();int rt = 0;
    for(int i = 1;i <= n;i++){
        fa[i] = read();c[i] = read();
        if(!fa[i])rt = i;
        edg[fa[i]].push_back(i);
    }
    dfs(rt);
    if(flag){
        puts("YES");
        sort(pr + 1,pr + 1 + n);
        for(int i = 1;i <= n;i++){ans[pr[i].second] = i;}
        for(int i = 1;i <= n;i++)printf("%d ",ans[i]);
        puts("");
    }
    else puts("NO");
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