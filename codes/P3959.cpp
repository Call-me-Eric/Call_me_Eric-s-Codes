#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
int n,m;
int wei[20][20];//wei[i][j] 是i->j的边值为wei[i][j]
int dep[20];
int tar[20][20];
int tot;
int p;
bool cmp(int a,int b){
    return wei[p][a] < wei[p][b];
}

int cnt;
int vis[20];
int tmp = 0,ans = inf;
void dfs(int num,int node){//TODO dfs
    for(int i = num;i <= cnt;i++){
        if(tot + tmp * dep[vis[i]] >= ans)return;
        for(int j = node;j <= tar[vis[i]][0];j++){
            if(!dep[tar[vis[i]][j]]){
                cnt++;
                vis[cnt] = tar[vis[i]][j];
                tmp -= wei[vis[cnt]][tar[vis[cnt]][1]];
                tot += wei[vis[i]][vis[cnt]] * dep[vis[i]];
                dep[vis[cnt]] = dep[vis[i]] + 1;
                dfs(i,j + 1);
                tmp += wei[vis[cnt]][tar[vis[cnt]][1]];
                tot -= wei[vis[i]][vis[cnt]] * dep[vis[i]];
                dep[vis[cnt]] = 0;
                cnt--;
            }
        }
        node = 1;
    }
    if(cnt == n){
        ans = min(tot,ans);
        return;
    }
}
int main(){//TODO main
    scanf("%d%d",&n,&m);
    int u,v,w;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            wei[i][j] = inf;
        }
    }
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&u,&v,&w);
        if(wei[u][v] < w)continue;
        if(wei[u][v] == inf){
            tar[v][++tar[v][0]] = u;
            tar[u][++tar[u][0]] = v;
        }
        wei[u][v] = wei[v][u] = w;
//      wei[u][v] = wei[v][u] = min(wei[u][v],w);//注意有重边
    }
    for(int i = 1;i <= n;i++){
        p = i;
        sort(tar[i] + 1,tar[i] + 1 + tar[i][0],cmp);
        tmp += wei[i][tar[i][1]];
    }
    for(int i = 1;i <= n;i++){
        tot = 0;
        cnt = 1;
        tmp -= wei[i][tar[i][1]];
        dep[i] = 1;
        vis[1] = i;
        dfs(i,1);
        dep[i] = 0;
        tmp += wei[i][tar[i][1]];
    }
    printf("%d",ans);
    return 0;
}