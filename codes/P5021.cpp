#include<bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 1e5 * 5 + 10;
int a[maxn];
int head[maxn];
struct road{
    int next_edge, to;
    int w;
}edge[maxn * 2];
int tot = 0;
int tot1 = 0;
int ans = 0;
bool check(int total){//TODO check
    int t = 0;
    int summ = 0;
    for(int i = 1;i < n;i++){
        if(summ + a[i]>= total){
            t++;
            summ = 0;
        }
        else summ += a[i];
    }
    return t >= m;
}
void dfs(int now,int fa){//TODO dfs
    for(int k = head[now];k;k = edge[k].next_edge){
        int v = edge[k].to;
        int w = edge[k].w;
        if(v != fa){
            dfs(v,now);
            a[++tot1] = w;
        }
    }
}
int dfs2(int now,int fa){//TODO dfs2
    int max1 = 0,max2 = 0;
    for(int k = head[now];k;k = edge[k].next_edge){
        int v = edge[k].to;
        int w = edge[k].w;
        if(v != fa){
            max2 = max(max2,dfs2(v,now) + w);
            if(max1 < max2)swap(max1,max2);
        }
    }
    ans = max(ans,max1 + max2);
    return max1;
}
void add(int u,int v,int w){//TODO add
    tot++;
    edge[tot].to = v;
    edge[tot].next_edge = head[u];
    edge[tot].w = w;
    head[u] = tot;
}
struct cmp{
    bool operator ()(int a,int b){
        return a > b;
    }
};
int main(){//TODO main
    scanf("%d%d",&n,&m);
    int u, v, w;
    bool book1 = 1;
    int sum = 0;
    for(int i = 1;i < n;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
        if(u != 1 && v != 1)book1 = 0;
        sum += w;
    }
    dfs(1,0);
    if(book1){
        sort(a + 1,a + n,cmp());
        ans = 99999999;
        for(int i = 1;i <= m;i++){
            ans = min(ans, a[i] + a[2 * m - i + 1]);
        }
        printf("%d",ans);
    }
    else if(m == 1){
        dfs2(1,0);
        printf("%d",ans);
    }
    else {
        int l = 1,r = sum,mid;
        while(l < r){
            mid = (l + r + 1) / 2;
            if(check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%d",l);
    }
    return 0;
}
/*
5 2
1 2 5
2 3 6
3 4 3
4 5 2

5 3
1 3 9
1 2 2
1 4 8
1 5 3
*/