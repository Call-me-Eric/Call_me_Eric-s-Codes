#include<bits/stdc++.h>
using namespace std;
int T;
int n, m, s, t;
const int inf = 0x3f3f3f3f;
const int maxn = 202;
struct edge{
    int next, v, cap,flow;
}e[maxn * maxn];
int first[maxn];
int tot;
int minn[maxn], maxx[maxn];
int in[maxn], out[maxn];

void add(int u,int v,int flow){
    e[tot].next = first[u];
    e[tot].flow = flow;
    e[tot].v = v;
    first[u] = tot++;
}
void addd(int u,int v,int flow){
    add(u,v,flow);
    add(v,u,-flow);
}
int d[maxn];
bool bfs(){
    memset(d,0,sizeof(d));
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = first[u];i;i = e[i].next){
            int v = e[i].v;
            if(!d[v] && 0 < e[i].flow){
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t)return 1;
            }
        }
    }
    return 0;
}
int dfs(int u,int flow){
    if(u == t)return flow;
    int rest = flow;
    for(int i = first[u];i;i = e[i].next){
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].cap > e[i].flow){
            int k = dfs(v,min(rest,e[i].cap - e[i].flow));
            if(!k) d[v] = 0;
            e[i].flow += k;
            e[i ^ 1].flow -= k;
            rest -= k;
        }
    }
    return flow - rest;
}

int main(){
    scanf("%d",&T);
    while(T--){
        int sum = 0;
        scanf("%d%d",&n,&m);
        s = n + 2; t = n + 1;
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        tot = 2;
        memset(first,0,sizeof(first));
        int u, v;
        int ans = 0;
        for(int i = 1;i <= m;i++){
            scanf("%d%d%d%d",&u,&v,&minn[i],&maxx[i]);
            addd(u,v,maxx[i] - minn[i]);
            in[v] += maxx[i];
            out[u] += maxx[i];
            sum += maxx[i];
            e[i].cap = maxx[i];
        }
        for(int i = 1;i <= m;i++){
            if(in[i] > out[i]){
                addd(s,i,in[i] - out[i]);
                sum += in[i] - out[i];
            }
            else{
                addd(i, t,out[i] - in[i]);
            }
        }
        while(bfs()){
            puts("GO");
            for(int i = 1;i <= n;i++)
                ans += dfs(s,inf);
        }
        if(ans < sum){
            puts("NO");
            printf("ans = %d,sum = %d",ans,sum);
        }
        else{
            puts("YES");
            for(int i = 1;i <= m;i++){
                printf("%d\n",minn[i] + e[i * 2 + 1].flow);
            }
        }
    }
    return 0;
}