#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10,maxm = 1e5 * 2 + 10;
int n, m;
int tot = 1;
int s,e;
int dis[maxm];
bool can[maxn], canbe[maxn];
queue<int> que;
vector<int> edge[maxn],dised[maxn];
int main(){
    int u = 0, v = 0;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        dised[v].push_back(u);
    }
    scanf("%d%d",&s,&e);
    can[e] = 1;
    que.push(e);
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(int i = dised[now].size() - 1;i >= 0;i--){
            int to = dised[now][i];
            if(!can[to]){
                que.push(to);
                can[to] = 1;
            }
        }
    }
    if(!can[s]){
        puts("-1");
        return 0;
    }
    for(int i = 1;i <= n;i++){
        if(can[i]){
            canbe[i] = 1;
            for(int j = edge[i].size() - 1;j >= 0;j--){
                int to = edge[i][j];
                if(!can[to]){
                    canbe[i] = 0;
                    break;
                }
            }
        }
    }
    if(!canbe[s]){
        puts("-1");
    }
    dis[s] = 1;
    que.push(s);
    while(!que.empty()){
        int now = que.front();que.pop();
        if(now == e){
            printf("%d\n",dis[e] - 1);
            return 0;
        }
        for(int i = edge[now].size() - 1;i >= 0;i--){
            int to = edge[now][i];
            if(canbe[to] && !dis[to]){
                dis[to] = dis[now] + 1;
                que.push(to);
            }
        }
    }
    puts("-1");
    return 0;
}