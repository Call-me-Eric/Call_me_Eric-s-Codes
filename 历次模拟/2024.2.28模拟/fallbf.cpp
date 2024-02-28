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
int n, m;
int val[maxn];
vector<int> edg[maxn];
namespace Subtask1{
int getans(int u,int va,int f){
    int x = 0, y = 0x3f3f3f3f;
    for(int v : edg[u])if(v != f){if(val[v] >= va && val[v] < y){x = v;y = val[v];}}
    if(x == 0){return u;}
    return getans(x,va,u);
}
void solve(){
    int opt, u, v;
    for(int test = 1;test <= m;test++){
        opt = read(); u = read();
        if(opt == 1){v = read();val[u] = v;}
        if(opt == 2){printf("%d\n",getans(1,u, 1));}
    }
}
};
namespace Subtask4{
pair<int,int> c[maxn];
int ans[maxn], X[maxn];
void getans(int u,int l,int r,int f){
    if(r < l)return;
    vector<pair<int,int> > vec;
    for(int v : edg[u]){if(v != f)vec.push_back(make_pair(val[v],v));}
    sort(vec.begin(),vec.end());int lp = l;
    for(auto i : vec){
        int x = i.first, v = i.second;
        x = upper_bound(X + l,X + r + 1,x) - X - 1;
        // printf("x = %d, i.first = %d,X[x] = %d\n",x,i.first,X[x]);
        getans(v,lp,x,u);lp = x + 1;
    }
    for(int i = lp;i <= r;i++)ans[c[i].second] = u;
}
void solve(){
    for(int i = 1;i <= m;i++){int opt = read();c[i] = make_pair(read(),i);}
    sort(c + 1,c + 1 + m);for(int i = 1;i <= m;i++)X[i] = c[i].first;//,printf("X[%d] = %d\n",i,X[i]);
    getans(1,1,m,1);
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
}
};
namespace Subtask3{
void solve(){
    int opt, u, v;set<pair<int,int> > st;
    for(int v : edg[1])st.insert(make_pair(val[v],v));
    for(int test = 1;test <= m;test++){
        opt = read(); u = read();
        if(opt == 1){
            v = read();
            auto it = st.lower_bound(make_pair(val[u],u));
            st.erase(it); st.insert(make_pair(val[u] = v, u));
        }
        if(opt == 2){
            auto it = st.lower_bound(make_pair(u,0));
            if(it->first != u)it++;
            printf("%d\n",it->second);
        }
    }
}
};
void main(){
    n = read(); m = read();int u, v;bool Sub3 = 1, Sub2 = 1;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
        if(u != 1)Sub3 = false; if(u + 1 != v)Sub2 = false;
    }
    Subtask1::solve();
    return;
}
};
bool edmemory;
signed main(){
    freopen("fall.in","r",stdin);
    freopen("fall.ans","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    // cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    // cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}