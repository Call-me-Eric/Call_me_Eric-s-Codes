#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;
int n, m;
int S, T;
int ans;
const int maxn = 1e6;
int tot = 1,Ans;
struct node{
    int next, v, c, w;
}E[maxn * 5];
int first[maxn];
int pre[maxn];
int len[maxn],dis[maxn];
bool book[maxn];
void add(int u,int v,int c,int w){
    tot++;
    E[tot].c = c;
    E[tot].v = v;
    E[tot].w = w;
    E[tot].next = first[u];
    first[u] = tot;
}
void addd(int u,int v,int c,int w){
    add(u,v,c,w);
    add(v,u,0,-w);
}
bool SPFA(int S){
    memset(dis,0x3f,sizeof(dis));
    memset(book,0,sizeof(book));
    memset(len,0,sizeof(len));
    queue<int> q;
    q.push(S);
    len[S] = 1e10;
    dis[S] = 0;
    book[S] = 1;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        book[x] = 0;
        for(int i = first[x];i;i = E[i].next){
            int v = E[i].v;
            if(!E[i].c)continue;
            if(dis[v] > dis[x] + E[i].w){
                dis[v] = dis[x] + E[i].w;
                len[v] = min(len[x],E[i].v);
                pre[v] = i;
                if(!book[v]){
                    book[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return len[n] > 0;
}
void dfs(int S){
    int x = n;
    while(x != S){
        int i = pre[x];
        E[i].c -= len[n];
        E[i ^ 1].c += len[n];
        x = E[i ^ 1].v;
    }
    ans += len[n] * dis[n];
    Ans += len[n];
}
int main(){
    while(scanf("%d%d",&n,&m) && n != 0 && m != 0){
        n++;
        S = n + 1;
        int a, b, d;
        tot = 1;
        ans = 0;
        memset(E,0,sizeof(E));
        memset(first,0,sizeof(first));
        memset(pre,0,sizeof(pre));
        memset(len,0,sizeof(len));
        memset(dis,0,sizeof(dis));
        memset(book,0,sizeof(book));
        for(int i = 1;i <= m;i++){
            scanf("%d%d%d",&a,&b,&d);
            a++; b++;
            addd(a,b,1,d);
        }
        addd(S,1,2,0);
        //if(SPFA(S)){
        //    dfs(S);
        Ans = 0;
        while(SPFA(S)){
            dfs(S);
        }
        /*if(Ans < 2){
            printf("Not possible\n");
        }
        else{*/
            printf("%d\n",ans);
        //}
    }
    return 0;
}