#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int n, m, q;
struct edge_{
    int next,v;
}e[maxn * 2];
int first[maxn];
int tot = 0;
void add(int u,int v){
    tot++;
    e[tot].next = first[u];
    e[tot].v = v;
    first[u] = tot;
}
int dis[maxn][2];//dis[a][0] : 偶数长度, dis[a][1] : 奇数长度
void bfs(){
    for(int i = 0;i <= 1;i++){
        for(int j = 0;j <= n;j++){
            dis[j][i] = 0x3f3f3f3f;
        }
    }
    queue<int> que;
    que.push(1);
    dis[1][0] = 0;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = first[u];i != 0;i = e[i].next){
            int v = e[i].v;
            bool flag = 0;
            if(dis[v][1] > dis[u][0] + 1){
                dis[v][1] = dis[u][0] + 1;
                que.push(v);
                flag = 1;
            }
            if(dis[v][0] > dis[u][1] + 1){
                dis[v][0] = dis[u][1] + 1;
                if(!flag)que.push(v);
            }
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    int u, v;
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    bfs();
    int a, L;
    for(int i = 1;i <= q;i++){
        scanf("%d%d",&a,&L);
        if(dis[a][L & 1] <= L){
            puts("Yes");
        }
        else puts("No");
    }
    return 0;
}