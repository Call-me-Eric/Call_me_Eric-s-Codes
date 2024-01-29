#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 200, maxm = 12000;
int n;
int a[maxn][maxn];

struct edge{
    int to, nexte, cap, cost, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int co  =0,int fl = 0):to(to),nexte(ne),cap(ca),cost(co),flow(fl) {}
}e[maxm];
int head[maxn], tot = 1;
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost);add(v, u, 0, -cost);}

int to[maxn], dis[maxn], limedg;
bool book[maxn];queue<int> que;
bool SPFA(int S,int T){
    while(!que.empty())que.pop();memset(book,0,sizeof(book));
    memset(dis,0x3f,sizeof(dis));memset(to,0,sizeof(to));
    que.push(S);dis[S] = 0;book[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();book[u] = 0;
        for(int i = head[u];i;i = e[i].nexte){
            if(i == limedg || i == (limedg ^ 1))continue;
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].cost && e[i].cap > e[i].flow){
                dis[v] = dis[u] + e[i].cost; to[v] = i;
                if(!book[v]){que.push(v);book[v] = 1;}
            }
        }
    }
    return to[T] != 0;
}
pair<int,int> MCMF(int S,int T){
    int maxcost = 0, maxflow = 0;
    while(SPFA(S,T)){
        int tmp = 0x3f3f3f3f;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            tmp = min(tmp,e[i].cap - e[i].flow);
        maxcost += tmp * dis[T];maxflow += tmp;
        for(int i = to[T];i;i = to[e[i ^ 1].to])
            e[i].flow += tmp,e[i ^ 1].flow -= tmp;
    }
    return make_pair(maxflow,-maxcost);
}

vector<pair<int,int> > res;
vector<int> tmp;
signed main(){
    n = read();int S = n * 2 + 1, T = n * 2 + 2;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] = read();
            addd(i,j + n,1,-a[i][j]);
        }
        addd(S,i,1,0);addd(i + n,T,1,0);
    }
    int ans = MCMF(S,T).second;printf("%d\n",ans);
    
    for(int u = 1;u <= n;u++)
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(v > n && v <= n * 2 && e[i].flow == 1){tmp.push_back(i);}
        }

    for(int i : tmp){
        for(int j = 1;j <= tot;j++)e[j].flow = 0;
        e[i].cap = e[i ^ 1].cap = -1;int temp = MCMF(S,T).second;
        // printf("u = %d, v = %d, flow = %d, i = %d\n",e[i ^ 1].to,e[i].to,temp,i);
        if(temp != ans)res.push_back(make_pair(e[i ^ 1].to, e[i].to));
        // for(int j = 1;j <= tot;j++){printf("i = %d u = %d v = %d cap = %d flow = %d cost = %d\n",j,e[j ^ 1].to,e[j].to,e[j].cap,e[j].flow,e[j].cost);}
        e[i].cap = e[i ^ 1].cap = 1;
    }

    sort(res.begin(),res.end());
    for(auto i : res)printf("%d %d\n",i.first,i.second - n);
    return 0;
}