#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  =getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, q;
vector<int> edg[maxn];
int dep[maxn], st[maxn], ed[maxn], idx;
int a[maxn], b[maxn], t[maxn];
void dfs(int u){st[u] = ++idx;for(int v : edg[u]){dep[v] = dep[u] + 1;dfs(v);}ed[u] = idx;}
void calc(int *a,int *p){
    for(int i = 1;i <= n;i++)b[i] = a[i];
    for(int i = 1;i <= n;i++)a[p[i]] = b[i];
}
signed main(){
    n = read(); q = read();
    for(int i = 1;i <= n;i++){a[i] = read();t[i] = 0;}
    for(int i = 2;i <= n;i++)edg[read()].push_back(i);
    dfs(1);calc(a,st);calc(dep,st);
    for(int tim = 1;tim <= q;tim++){
        int u = read();int sumdep = 0, cnt = 0;
        for(int i = st[u];i <= ed[u];i++){
            if(t[i] <= tim){
                cnt++;sumdep += dep[i];
                t[i] = tim + a[i];
            }
        }
        sumdep -= cnt * dep[st[u]];
        printf("%d %d\n",sumdep,cnt);
    }
    return 0;
}