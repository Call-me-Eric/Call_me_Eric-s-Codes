#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e5 + 10,INF = 0x3f3f3f3f3f3f3f3f;
int n, q;
int a[maxn], l[maxn], r[maxn];
typedef pair<int,int> pii;
vector<pii> edg[maxn];
vector<pii> qry[maxn];
int stk[maxn], top;

int dis[maxn];bool book[maxn];
priority_queue<pii,vector<pii>,greater<pii> > que;
int ans[maxn];

void solve(){
    n = read(); q = read();
    for(int i = 1;i <= n;i++)edg[i].clear();
    for(int i = 1;i <= n;i++)a[i] = read();
    for(int i = 1;i <= n;i++){l[i] = read(), r[i] = read();}
    for(int i = 1;i <= q;i++){
        int s = read(), t = read();
        qry[s].push_back(make_pair(t,i));
    }
    int totedge = 0;
    top = 0;
    for(int i = 1;i <= n;i++){
        for(int j = top;j;j--){
            totedge++;
            edg[i].push_back(make_pair(stk[j],l[i]));
            if(a[stk[j]] >= a[i])break;
        }
        while(top && a[stk[top]] <= a[i])top--;
        stk[++top] = i;
    }
    top = 0;
    for(int i = n;i;i--){
        for(int j = top;j;j--){
            totedge++;
            edg[i].push_back(make_pair(stk[j],r[i]));
            if(a[stk[j]] >= a[i])break;
        }
        while(top && a[stk[top]] <= a[i])top--;
        stk[++top] = i;
    }
    cerr << "totedge = " << totedge << endl;
    for(int s = 1;s <= n;s++){
        if(!qry[s].size())continue;
        while(!que.empty())que.pop();
        for(int j = 1;j <= n;j++)dis[j] = INF, book[j] = 0;
        que.push(make_pair(0,s));dis[s] = 0;
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
        for(auto i : qry[s]){ans[i.second] = dis[i.first];}
    }
    for(int i = 1;i <= q;i++)printf("%lld\n",ans[i]);
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("railway.in","r",stdin);
    freopen("railway.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}