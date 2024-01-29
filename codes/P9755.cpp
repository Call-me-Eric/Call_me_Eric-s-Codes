#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, INF = 1e18;

int n, a[maxn], b[maxn], c[maxn], z[maxn];
vector<int> edg[maxn];


int d[maxn], dep[maxn];
bool check1(int l,int r,int i){
    int res = 0;
    if(l >= z[i])return r - l + 1 >= a[i];
    if(r >= z[i]){res += r - z[i] + 1;r = z[i] - 1;}
    if(res >= a[i])return true;
    return max(b[i] + c[i] * l,1ll) + max(b[i] + c[i] * r,1ll) > ((a[i] - res) * 2 - 1) / (r - l + 1);
}
int buc[maxn];
int dfs(int u,int f){
    int minn = d[u];
    for(int v : edg[u])
        if(v != f){minn = min(minn,dfs(v, u));}
    if(minn <= n)buc[minn]++;
    return minn;
}
bool check(int maxtime){
    for(int i = 1;i <= n;i++){
        int l = 1, r = maxtime, mid = 0;d[i] = 0;
        while(l <= r){
            mid = l + r >> 1;
            if(check1(mid,maxtime,i)){l = mid + 1,d[i] = mid;}
            else r = mid - 1;
        }
        if(!d[i])return false;
    }
    memset(buc,0,sizeof(buc));dfs(1 ,0);
    for(int i = 1;i <= n;i++){
        buc[i] += buc[i - 1];
        if(buc[i] > i)return false;
    }
    return true;
}

signed main(){
    n = read();int u, v;
    for(int i = 1;i <= n;i++){
        a[i] = read(); b[i] = read(); c[i] = read();
        if(c[i] < 0)z[i] = (b[i] - 1 - c[i]) / (-c[i]);
        else z[i] = INF + 1;
    }
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    int l = 1, r = 1e9, mid = 0, ans = -1;
    while(l <= r){
        mid = l + r >> 1;
        if(check(mid)){r = mid - 1;ans = mid;}
        else l = mid + 1;
    }
    printf("%lld\n",ans);
    return 0;
}