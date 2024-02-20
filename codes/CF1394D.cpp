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
const int maxn = 2e5 + 10;
int n, a[maxn], b[maxn];
vector<int> edg[maxn];
int f[maxn][2];
int ans = 0x3f3f3f3f3f3f3f3f;
void dfs(int u,int fa){
    int in = 0, out = 0, sum = 0;
    f[u][0] = f[u][1] = 0x3f3f3f3f3f3f3f3f;
    for(int v : edg[u]){
        if(v != fa){
            dfs(v, u);
            if(b[v] < b[u]){sum += f[v][0];in++;}
            if(b[v] > b[u]){sum += f[v][1];out++;}
        }
    }
    vector<int> vec;
    for(int v : edg[u]){
        if(v != fa && b[v] == b[u]){
            sum += f[v][1];out++;
            vec.push_back(f[v][0] - f[v][1]);
        }
    }
    sort(vec.begin(),vec.end());vec.insert(vec.begin(),0);
    for(int i : vec){
        sum += i;
        if(u == 1)ans = min(ans,sum + max(in,out) * a[u]);
        else{
            f[u][0] = min(f[u][0],sum + max(in,out + 1) * a[u]);
            f[u][1] = min(f[u][1],sum + max(in + 1,out) * a[u]);
        }
        in++;out--;
    }
}
void main(){
    n = read();int u, v;
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++)b[i] = read();
    for(int i = 1;i < n;i++){
        u = read(), v=  read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 0);
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