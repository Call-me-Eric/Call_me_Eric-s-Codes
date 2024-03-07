#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10, maxk = 1e4 + 10, maxm = 3e5 + 10;

int n, m, k;
struct edge{
    int u, v, w, id;
    edge(int u = 0,int v = 0,int w = 0,int id = 0):u(u),v(v),w(w),id(id){}
    friend bool operator < (edge a,edge b){return a.w > b.w;}
}edg[maxm];
int id[maxm];

int fa[maxn][maxk];
int getf(int x,int lvl){return fa[x][lvl] == x ? x : fa[x][lvl] = getf(fa[x][lvl],lvl);}

signed main(){
    freopen("hoshi.in","r",stdin);
    freopen("hoshi.out","w",stdout);
    n = read(); m = read(); k = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        edg[i] = edge(u,v,w,i);
    }
    
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= k;j++){
            fa[i][j] = i;
        }
    }
    sort(edg + 1,edg + 1 + m);

    for(int i = 1;i <= m;i++){
        int l = 1, r = k, ans = 0, mid;
        while(l <= r){
            mid = l + r >> 1;
            if(getf(edg[i].u,mid) != getf(edg[i].v,mid)){
                ans = mid;r = mid - 1;
            }
            else l = mid + 1;
        }
        id[edg[i].id] = ans;
        if(ans)fa[getf(edg[i].u,ans)][ans] = getf(edg[i].v,ans);
    }
    for(int i = 1;i <= m;i++)printf("%d\n",id[i]);
    return 0;
}