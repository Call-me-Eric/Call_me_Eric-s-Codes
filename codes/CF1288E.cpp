#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 6e5 + 10;
int n, m;
int ansl[maxn],ansr[maxn], pos[maxn];
struct BIT{
    int c[maxn << 2];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int upd){for(;x <= n + m;x += lowbit(x))c[x] += upd;}
    int qry(int x){int ans = 0;for(;x;x -=lowbit(x))ans += c[x];return ans;}
}tree;
signed main(){
    n =  read(); m = read();
    for(int i = 1;i <= n;i++){
        ansl[i] = ansr[i] = i;
        pos[i] = i + m;
        tree.upd(i + m,1);
    }
    for(int i = 1;i <= m;i++){
        int u = read();ansl[u] = 1;
        ansr[u] = max(ansr[u],tree.qry(pos[u]));
        tree.upd(pos[u],-1);pos[u] = m - i + 1;
        tree.upd(pos[u],1);
    }
    for(int i = 1;i <= n;i++){ansr[i] = max(ansr[i],tree.qry(pos[i]));}
    for(int i = 1;i <= n;i++)printf("%d %d\n",ansl[i],ansr[i]);
    return 0;
}