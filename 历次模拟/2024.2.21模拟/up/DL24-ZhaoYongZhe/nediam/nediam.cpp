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
const int maxn = 7e3 + 10;
int n, m;
int nediam(vector<int> vec,int l = 0,int r = n - 1){
    // printf("l = %d, r = %d\n",l,r);
    int n = vec.size();
    if(n == 1)return vec[0];
    if(n == 2){return min(vec[0],vec[1]);}
    int tl = (n - 1) / 3 + 1;
    int tr = (2 * n - 1) / 3 + 1;
    vector<int> c,vec1[3];
    for(int i = 0;i < tl;i++)vec1[0].push_back(vec[i]);
    c.push_back(nediam(vec1[0],l,tl - 1));
    for(int i = tl;i < tr;i++)vec1[1].push_back(vec[i]);
    c.push_back(nediam(vec1[1],tl,tr - 1));
    for(int i = tr;i < n;i++)vec1[2].push_back(vec[i]);
    c.push_back(nediam(vec1[2],tr,r));
    sort(c.begin(),c.end());
    // printf("nediam[%d,%d] = %d\n",l,r,c[1]);
    return c[1];
}
int getmid(vector<int> vec){
    sort(vec.begin(),vec.end());
    return vec[(vec.size() + 1) / 2 - 1];
}
vector<int> vec;
int ans, a[maxn];
void dfs(int u){
    if(u == n){
        if(nediam(vec) == getmid(vec))ans++;
        return;
    }
    if(a[u] != -1){vec[u] = a[u];dfs(u + 1);}
    else for(int i = 0;i < m;i++){vec[u] = i;dfs(u + 1);vec[u] = -1;}
}
void solve(){
    n = read(); m = read();
    for(int i = 0;i < n;i++)a[i] = read();
    vec.resize(n);
    dfs(0); printf("%d\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("nediam.in","r",stdin);
    freopen("nediam.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
3
6 5
‐1 1 4 5 1 4
7 9
1 9 ‐1 9 8 ‐1 0
*/