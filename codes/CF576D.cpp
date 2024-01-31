#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 155;
int n, m;
struct edge{
    int u, v, w;
    edge(int u = 0,int v = 0,int w = 0):u(u),v(v),w(w){}
    friend bool operator < (edge a,edge b){return a.w < b.w;}
}edg[maxn];

struct Matrix{
    bitset<maxn> a[maxn];
    Matrix(bool opt = 0){for(int i = 1;i <= n;i++){a[i].reset(n);a[i][i] = opt;}}
    friend Matrix operator * (Matrix a,Matrix b){
        Matrix c = Matrix();
        for(int i = 1;i <= n;i++)
            for(int k = 1;k <= n;k++)
                if(a.a[i][k])
                    c.a[i] |= b.a[k];
        return c;
    }
    friend Matrix operator ^ (Matrix a,int b){
        Matrix res = Matrix(1);
        while(b){
            if(b & 1)res = res * a;
            a = a * a;b >>= 1;
        }
        return res;
    }
}A,B;

int dis[maxn];
queue<int> que;
void bfs(){
    memset(dis,0x3f,sizeof(dis));
    while(!que.empty())que.pop();
    for(int i = 1;i <= n;i++)
        if(A.a[1][i]){que.push(i);dis[i] = 0;}
    if(!dis[n])return;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int v = 1;v <= n;v++)
            if(B.a[u][v] && dis[v] == 0x3f3f3f3f3f3f3f3f){
                dis[v] = dis[u] + 1;que.push(v);
            }
    }
}

signed main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        edg[i] = edge(u, v, w);
    }
    sort(edg + 1,edg + 1 + m);
    int tim = 0,ans = 0x3f3f3f3f;dis[n] = 0x3f3f3f3f;
    A = Matrix(1);B = Matrix();edg[m + 1].w = -1;
    for(int i = 1;i <= m;i++){
        if(ans < edg[i].w)break;
        int dif = edg[i].w - tim;tim = edg[i].w;
        A = A * (B ^ dif); B.a[edg[i].u][edg[i].v] = 1;
        if(edg[i].w != edg[i + 1].w)bfs();
        ans = min(ans,tim + dis[n]);
    }
    if(ans == 0x3f3f3f3f)puts("Impossible");
    else printf("%lld\n",ans);
    return 0;
}