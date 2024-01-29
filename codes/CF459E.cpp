#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=  0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = - 1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10;
int n ,m;
struct edge{
    int fr, to;
    edge(int fr = 0,int to = 0):fr(fr),to(to){}
};
vector<edge> vec[maxn];
int f[maxn], tmp[maxn];
signed main(){
    n = read(); m = read(); int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v=  read(); w= read();
        vec[w].push_back(edge(u, v));
    }
    for(int i = 1;i <= 1e5;i++){
        for(auto u : vec[i]){tmp[u.to] = f[u.to];tmp[u.fr] = f[u.fr];}
        for(auto u : vec[i]){f[u.to] = max(f[u.to],tmp[u.fr] + 1);}
    }

    int ans = 0;
    for(int i = 1;i <= n;i++)ans = max(ans,f[i]);
    printf("%d\n",ans);
    
    return 0;
}