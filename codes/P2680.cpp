#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
int n,m;
int first[maxn];
int st[maxn],en[maxn];
int a[maxn];
int fa[maxn];//fa is edge
struct nodee{
    int nexte,v;
    int w;
}e[maxn * 2];
int tot;
int dep[maxn];
int book[maxn];
int sum[maxn];
void add(int u,int v,int w){
    tot++;
    e[tot].nexte = first[u];
    e[tot].v = v;
    e[tot].w = w;
    first[u] = tot;
}
void dfs1(int u,int f){
    for(int i = first[u];i;i = e[i].nexte){
        int v = e[i].v;
        int w = e[i].w;
        if(v == f){
            fa[u] = i;
            continue;
        }
        dep[v] = dep[u] + 1;
        dfs1(v,u);
    }
}
void do1(){
    dfs1(1,-1);
    int maxe = -99;
    int dis = 0;
    if(dep[st[1]] < dep[en[1]]){swap(st[1],en[1]);}
    while(dep[st[1]] > dep[en[1]]){
        if(e[fa[st[1]]].w > maxe)maxe = e[fa[st[1]]].w;
        dis += e[fa[st[1]]].w;
        st[1] = e[fa[st[1]]].v;
    }
    while(st[1] != en[1]){
        if(e[fa[st[1]]].w > maxe)maxe = e[fa[st[1]]].w;
        dis += e[fa[st[1]]].w;
        st[1] = e[fa[st[1]]].v;
        if(e[fa[en[1]]].w > maxe)maxe = e[fa[en[1]]].w;
        dis += e[fa[en[1]]].w;
        en[1] = e[fa[en[1]]].v;
    }
    printf("%d",dis - maxe);
}
void do2(){
    sum[1] = 0;
    for(int i = 2;i <= n;i++){
        sum[i] = sum[i - 1] + a[i - 1];
    }
    int res = 99999999;
    for(int i = 1;i < n;i++){
        int ans = 0,tmp = 0;
        for(int j = 1;j <= m;j++){
            tmp = sum[en[j]] - sum[st[j]];
            if(en[j] > i && st[j] <= i)tmp -= a[i];
            ans = max(ans,tmp);
        }
        res = min(ans,res);
    }
    printf("%d",res);
}
int main(){
    scanf("%d%d",&n,&m);
    int u,v,w;
    for(int i = 1;i < n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
        if(m != 0){
            a[u] = w;
        }
    }
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&st[i],&en[i]);
    }
    if(m == 1){
        do1();
    }
    else{
        do2();
    }
    return 0;
}
/*
7 3
1 2 1
2 3 2
3 4 9
4 5 8
5 6 1
6 7 10
1 4
3 6
5 7
*/