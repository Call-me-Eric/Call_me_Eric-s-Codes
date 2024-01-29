#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n,m;
int first[maxn];
struct nodee{
    int nexte,v;
}e[maxn * 2];
int tot;
int w[maxn];
int s[maxn],t[maxn];
int dep[maxn];
int ans[maxn];
int book[maxn];
void add(int u,int v){
    tot++;
    e[tot].nexte = first[u];
    e[tot].v = v;
    first[u] = tot;
}
void dfs1(int now,int fa,int depth){
    dep[now] = depth;
    for(int i = first[now];i;i = e[i].nexte){
        int v = e[i].v;
        if(v == fa)continue;
        dfs1(v,now,depth + 1);
    }
}
int dfs2(int now,int fa){
    int cnt = book[now];
    for(int i = first[now];i;i = e[i].nexte){
        int v = e[i].v;
        if(v == fa)continue;
        cnt += dfs2(v,now);
    }
    if(w[now] == dep[now])ans[now] = cnt;
    return cnt;
}
int main(){
    int u, v;
    bool tot1 = 1;//s[i] = 1
    bool tot2 = 1;//t[i] = 1
    bool tot3 = 1;//w[i] = 0
    bool tot4 = 1;//s[i] = t[i]
    scanf("%d%d",&n,&m);
    for(int i = 1;i < n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    for(int i = 1;i <= n;i++){
        scanf("%d",&w[i]);
        if(w[i] != 0)tot3 = 0;
    }
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&s[i],&t[i]);
        if(s[i] != t[i])tot4 = 0;
        if(s[i] != 1)tot1 = 0;
        if(t[i] != 1)tot2 = 0;
    }
    if(tot4){
        for(int i = 1;i <= m;i++){
            if(w[s[i]] == 0)ans[s[i]]++;
        }
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
    }
    else if(tot3){
        for(int i = 1;i <= m;i++){
            ans[s[i]]++;
        }
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
    }
    else if(tot1){
        dfs1(1,-1,0);
        for(int i = 1;i <= n;i++){
            book[t[i]]++;
        }
        int cnt = dfs2(1,0);
        if(!w[1]) ans[1] = cnt;
        for(int i = 1;i <= n;i++){
            printf("%d ",ans[i]);
        }
    }
    return 0;
}
/*
8 8
1 2
2 3
1 4
1 5
1 6
6 7
6 8
0 1 2 1 1 1 2 2
1 3
1 7
1 4
1 5
1 3
1 7
1 4
1 5
*/