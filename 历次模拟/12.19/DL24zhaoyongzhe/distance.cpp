#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, maxk = 512;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
struct Bigint{
    bitset<maxk> c;
    Bigint(bitset<maxk> x){c = x;}
    Bigint(int pos = -2){
        if(pos != -2 && pos != -1)c.set(pos);
        else if(pos == -2)c.set();
        else c.reset();
    }
    friend bool operator < (Bigint a,Bigint b){
        for(int i = maxk - 1;i;i--){if(a.c[i] != b.c[i])return a.c[i] < b.c[i];}
        return false;
    }
    friend bool operator == (Bigint a,Bigint b){
        for(int i = maxk - 1;i;i--){if(a.c[i] != b.c[i])return false;}
        return true;
    }
    friend bool operator > (Bigint a,Bigint b){
        for(int i = maxk - 1;i;i--){if(a.c[i] != b.c[i])return a.c[i] > b.c[i];}
        return false;
    }
};
Bigint add(Bigint a,Bigint b){
    bitset<maxk> x = a.c | b.c, y = a.c & b.c;
    if(y.none())return Bigint(x);
    return add(Bigint(x),Bigint(y << 1));
}
Bigint operator + (Bigint a,Bigint b){return add(a, b);}
int n, x[maxk], y[maxk];
bool book[maxk];
Bigint dis[maxk];
Bigint e(int u,int v){
    return Bigint(max(abs(x[u] - x[v]),abs(y[u] - y[v])));
}
priority_queue<pair<Bigint,int>,vector<pair<Bigint,int> >,greater<pair<Bigint,int> > > que;
int pre[maxn];
void dijsktra(int S,int T){
    for(int i = 1;i <= n;i++)dis[i] = Bigint();
    dis[S] = Bigint(-1);que.push(make_pair(dis[S],S));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(int v = 1;v <= n;v++){
            Bigint w = e(u,v);
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                pre[v] = u;
                que.push(make_pair(dis[v],v));
            }
        }
    }
}
signed main(){
    freopen("distance.in","r",stdin);
    freopen("distance.out","w",stdout);
    read();read();n = read();
    for(int i = 1;i <= n;i++){
        x[i] = read(); y[i] = read();
    }
    dijsktra(1, n);
    stack<int> stk;int u = n;
    while(pre[u]){stk.push(u);u = pre[u];}
    stk.push(1);printf("%d\n",stk.size());
    while(!stk.empty()){printf("%d ",stk.top());stk.pop();}
    return 0;
}