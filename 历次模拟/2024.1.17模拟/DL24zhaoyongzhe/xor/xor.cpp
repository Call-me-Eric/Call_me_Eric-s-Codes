#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =  getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 61;
int a[maxn][maxn], n;
bool book[maxn];
bool f[1 << 12];
map<int,vector<int> > mp[maxn];
int mx = 0;
int endn = 0;
// map<int,vector<int> > v[2];
// void dfs(int u,int sta,int stat){
//     if(u == endn + 1){
//         bool opt = (endn != n / 2),tmp = true;
//         for(int x : v[opt][stat]){if(x == sta){tmp = false;break;}}
//         if(tmp)v[opt][stat].push_back(sta);
//         return;
//     }
//     for(int i = 1;i <= n;i++){
//         if(!((1 << (i - 1)) & stat))continue;
//         dfs(u + 1,sta ^ a[u][i],stat ^ (1 << (i - 1)));
//     }
// }
vector<int> dfs1(int u,int sta){
    // printf("u = %d, sta = %d\n",u,sta);
    if(u == endn + 1){vector<int> vec;vec.push_back(0);return vec;}
    if(mp[u][sta].size())return mp[u][sta];
    for(int i = 1;i <= n;i++){
        if(!((1 << (i - 1)) & sta))continue;
        auto v = dfs1(u + 1,sta ^ (1 << (i - 1)));
        if(!mp[u].count(sta)){vector<int> vec;vec.clear();mp[u][sta] = vec;}
        for(int j : v)mp[u][sta].push_back(j ^ a[u][i]);
        sort(mp[u][sta].begin(),mp[u][sta].end());
        mp[u][sta].erase(unique(mp[u][sta].begin(),mp[u][sta].end()),mp[u][sta].end());
        if(mp[u][sta].size() == mx)break;
    }
    return mp[u][sta];
}
inline int lowbit(int x){return x & (-x);}
inline int popcount(int x){int cnt = 0;for(;x;x >>= 1)cnt += (x & 1);return cnt;}
signed main(){
    freopen("xor.in","r",stdin);
    freopen("xor.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] = read();mx = max(mx,a[i][j]);
        }
    }
    while(mx - lowbit(mx) > 0){mx -= lowbit(mx);}
    mx <<= 1;//cerr << mx << endl;
    if(n >= 40){
        for(int i = 0;i < mx;i++){printf("%d ",i);}
        return 0;
    }
    endn = n;dfs1(1, (1 << n) - 1);
    for(int v : mp[1][(1 << n) - 1]){f[v] = 1;}
    // endn = n / 2;dfs(1, 0,(1 << n) - 1);
    for(int i = 0;i < (1 << 12);i++){
        if(f[i])printf("%d ",i);
    }
    return 0;
}