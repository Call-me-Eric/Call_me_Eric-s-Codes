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
int n, m;
vector<int> edg[maxn];
vector<pair<int,int> > vec[maxn];
int dep[maxn];

set<pair<int,int> > st[maxn];
int id[maxn], tag[maxn];

void del(int u,int lim){
    while(!st[id[u]].empty()){
        auto it = st[id[u]].end();it--;
        if((it->first) <= lim)return;
        st[id[u]].erase(it);
    }
}
void ins(int u,pair<int,int> val){
    u = id[u];val.second -= tag[u];
    auto it = st[u].lower_bound(make_pair(val.first,-0x3f3f3f3f3f3f3f3f));
    if(it != st[u].end() && (it->first) == val.first){
        if(it->second > val.second){
            st[u].erase(it);st[u].insert(val);
        }
    }
    else{
        if(it != st[u].begin() && (--it)->second <= val.second)return;
        st[u].insert(val);
    }
    auto s = st[u].lower_bound(make_pair(val.first + 1,-0x3f3f3f3f3f3f3f3f));
    auto t = s;
    while(t != st[u].end() && (t->second) >= val.second)++t;
    if(t != it)st[u].erase(s,t);
}
void dfs(int u,int f){
    dep[u] = dep[f] + 1;id[u] = u;
    for(auto i : vec[u])ins(u,make_pair(dep[i.first],i.second));
    ins(u,make_pair(dep[u],0));
    int sum = 0;
    for(int v : edg[u]){
        if(v != f){
            dfs(v, u); del(v,dep[u]);
            if(!st[id[v]].size()){puts("-1");exit(0);}
            int tmp = st[id[v]].rbegin()->second + tag[id[v]];
            sum += tmp;tag[id[v]] -= tmp;
            if(st[id[v]].size() > st[id[u]].size())swap(id[u],id[v]);
            for(auto it = st[id[v]].begin();it != st[id[v]].end();it++)
                ins(u,make_pair(it->first,it->second + tag[id[v]]));
            st[id[v]].clear();
        }
    }
    tag[id[u]] += sum;
}
void main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        if(u == v)continue;
        vec[u].push_back(make_pair(v, w));
    }
    dfs(1, 0);del(1,1);
    printf("%lld\n",st[id[1]].rbegin()->second + tag[id[1]]);
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