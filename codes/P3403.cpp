#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int h, a, b, c;
typedef pair<int,int> pii;
vector<pii> edg[maxn];
int dis[maxn];bool book[maxn];
priority_queue<pii,vector<pii>,greater<pii> > que;
signed main(){
    h = read() - 1;a = read(); b = read(); c = read();
    for(int i = 0;i < a;i++){
        edg[i].push_back(make_pair((i + b) % a,b));
        edg[i].push_back(make_pair((i + c) % a,c));
        dis[i] = 0x3f3f3f3f3f3f3f3f;
    }
    dis[0] = 0;que.push(make_pair(dis[0],0));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                que.push(make_pair(dis[v],v));
            }
        }
    }
    int ans = 0;
    for(int i = 0;i < a;i++)
        if(dis[i] <= h){ans += (h - dis[i]) / a + 1;}
    printf("%lld\n",ans);
    return 0;
}