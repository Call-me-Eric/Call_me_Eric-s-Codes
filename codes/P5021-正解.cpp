#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e4 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int topoint = 0,int nextedge = 0,int weight = 0){
        this->nextedge = nextedge; this->topoint = topoint; this->weight = weight;
    }
}e[maxn * 2];
int total[maxn], f[maxn];
vector<int> son[maxn];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
int check(int u,int pos,int tota,int limit){
    int res = 0, l = 0;
    for(int r = tota - 1;r;r--){
        r -= (r == pos);
        while(l < r && son[u][l] + son[u][r] < limit)l++;
        l += (l == pos);
        if(l >= r)break;
        res++;l++;
    }
    return res;
}
void dfs(int u,int fa,int limit){
    f[u] = total[u] = 0; son[u].clear();
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(v == fa)continue;;
        dfs(v,u,limit);
        f[v] += w;
        if(f[v] >= limit)total[u]++;
        else son[u].push_back(f[v]);
    }
    int tott = son[u].size();
    sort(son[u].begin(),son[u].end());
    int l = 0, r = 0, sub = 0, res = 0;
    for(r = tott - 1;r;r--){//将无法单链就超过 limit 的链拼起来拼成两个链让其大于 limit
        while(l < r && son[u][l] + son[u][r] < limit)l++;
        if(l >= r)break; sub++; l++;
    }
    total[u] += sub;
    if(sub * 2 == tott) return;//如果已经能够两两匹配完成
    l = 0;r = tott - 1;//否则找一个在满足上述匹配成立的前提下最长的剩下的链
    while(l <= r){
        int mid = (l + r) >> 1;
        int temp = check(u, mid, tott, limit);
        if(temp == sub){res = mid;l = mid + 1;}
        else r = mid - 1;
    }
    f[u] = son[u][res];
}
bool check(int mid){
    int res = 0;
    dfs(1,0,mid);
    for(int i = 1;i <= n;i++)
        res += total[i];
    return res >= m;
}
signed main(){
    int u, v, w,totwei = 0;
    int l = 0, r = 0, ans = -1;
    n = read(); m = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u,v,w); add(v,u,w);
        totwei += w;
    }
    r = totwei;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(check(mid)){l = mid;ans = mid;}
        else r = mid - 1;
    }
    printf("%lld\n",l);
    return 0;
}