#include<bits/stdc++.h>
using namespace std;
int n, m;
struct node{
    int u,v,w;
};
const int maxn = 10000 + 10,maxm = maxn * maxn / 2,INF = 0x3f3f3f3f;
node e[maxn];
int f[maxn];
int getf(int x){
    if(f[x] == x)return x;
    else{
        f[x] = getf(f[x]);
        return f[x];
    }
}
int kruskal(int a){
    for(int i = 1;i <= n;i++)f[i] = i;
    int cnt = 0;
    for(int i = a;i <= m;i++){
        int f1 = getf(e[i].u);
        int f2 = getf(e[i].v);
        if(f1 != f2){
            cnt++;
            if(cnt == n - 1){
                return e[i].w - e[a].w;
            }
            f[f2] = f1;
        }
    }
    return INF;
}
struct cmp{
    bool operator ()(node a,node b){
        return a.w < b.w;
    }
};
int main(){
    scanf("%d%d",&n,&m);
    int u,v,w;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    if(m < n - 1 || kruskal(1) == INF){
        printf("-1");
        return 0;
    }
    int ans = INF;
    sort(e + 1,e + 1 + m,cmp());
    for(int i = 1;i <= m;i++){
        int sum = kruskal(i);
        if(sum == INF)continue;
        ans = min(ans,sum);
    }
    printf("%d",ans);
    return 0;
}