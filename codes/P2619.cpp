#include<bits/stdc++.h>
using namespace std;
inline int  read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, m, need;
struct edge{
    int from,to, wei, col;
    edge(int from = 0,int to = 0,int w = 0,int col = 0):from(from),to(to),wei(w),col(col){}
}e[maxn << 1];
bool operator < (edge a,edge b){if(a.wei == b.wei)return a.col > b.col;return a.wei < b.wei;}

int fa[maxn];
int getf(int x){return x == fa[x] ? x :fa[x] = getf(fa[x]);}

signed main(){
    n = read() + 1; m = read();need = read();int u, v, w, col;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read(); col = read();
        e[i] = edge(u + 1,v + 1,w,!col);
    }
    int l = -114514, r = 114514, mid = 0, ans = -1;
    while(l <= r){
        mid = l + r >> 1;
        for(int i = 1;i <= m;i++){e[i].wei += e[i].col * mid;}
        sort(e + 1,e + 1 + m);
        int sum = 0, tot = 0, tcol = 0;
        for(int i = 1;i <= n;i++)fa[i] = i;
        for(int i = 1;i <= m && tot < n;i++){
            u = e[i].from, v = e[i].to;
            int fu = getf(u), fv = getf(v);
            if(fu != fv){
                fa[fu] = fv;tot++;
                tcol += e[i].col;
                sum += (e[i].wei);
            }
        }
        if(tcol >= need){l = mid + 1;ans = sum - need * mid;}
        else {r = mid - 1;}
        for(int i = 1;i <= m;i++){e[i].wei -= e[i].col * mid;}
    }
    printf("%d\n",ans);
    return 0;
}