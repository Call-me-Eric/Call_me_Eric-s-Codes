#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e2 + 10, maxm = 5e4 + 10;
int n, m;
int G, S;
struct edge{
    int u, v, g, s, nexte;
    edge(int u = 0,int v = 0,int g = 0,int s = 0,int ne = 0):u(u),v(v),g(g),s(s),nexte(ne){}
    friend bool operator < (edge a,edge b){return a.s < b.s;}
}e[maxm],edg;
int gold[maxm];

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
multiset<edge> E;
typedef multiset<edge>::iterator iter;
bool check(int mid){
    int cnt = 1;
    for(int i = 1;i <= n;i++){fa[i] = i;}
    for(iter it = E.begin();it != E.end();it++){
        edg = *it;int fu = getf(edg.u), fv = getf(edg.v);
        if(fu == fv || edg.g > mid)continue;
        fa[fu] = fv;cnt++;
    }
    return cnt >= n;
}

signed main(){
    int u, v, g, s, ans = 0x3f3f3f3f3f3f3f3f;
    n =  read(); m = read();G = read(); S = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); g = read(); s = read();
        gold[i] = g;
        e[i] = edge(u,v,g,s);E.insert(e[i]);
    }
    sort(gold + 1,gold + 1 + m);
    int l = 1, r = m, res = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(gold[mid])){r = mid - 1;res = mid;}
        else l = mid + 1;
    }
    if(res == -1){puts("-1");return 0;}
    for(int point = res;point <= m;point++){
        int cnt = 1, maxx = 0;
        for(int j = 1;j <= n;j++)fa[j] = j;
        for(iter it = E.begin();it != E.end();it++){
            edg = *it;int fu = getf(edg.u), fv = getf(edg.v);
            if(edg.g > gold[point])continue;
            if(fu == fv){iter tmp = it;tmp--;E.erase(it);it = tmp;}
            else{fa[fu] = fv;maxx = edg.s;cnt++;}
            if(cnt == n)break;
        }
        if(cnt == n)ans = min(ans,maxx * S + gold[point] * G);
    }
    printf("%lld\n",ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans);
    return 0;
}