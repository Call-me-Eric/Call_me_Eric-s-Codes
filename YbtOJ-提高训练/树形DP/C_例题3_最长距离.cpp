#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 10010;
int head[maxn], tot;
struct edge{
    int topoint,nextedge,weight;
}e[maxn * 3];
int bigson[maxn];
int dp[maxn][3];//dp[i][0]以i为根的最长路径
                //dp[i][1]以i为根的次长路径(不一定<dp[i][0])
                //dp[i][2]以fa[i]为根的不经过i的最长路径
void add(int u,int v,int w){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    e[tot].weight = w;
    head[u] = tot;
}
void dfs1(int root,int fa){
	for(int i = head[root];i;i = e[i].nextedge){
		int v = e[i].topoint, w = e[i].weight;
		if(v == fa)continue;
		dfs1(v, root);
		if(dp[root][0] < dp[v][0] + w){
			dp[root][0] = dp[v][0] + w;
			bigson[root] = v;
		}
	}
	for(int i = head[root];i;i = e[i].nextedge){
		int v = e[i].topoint, w = e[i].weight;
		if(v == fa)continue;
		if(v == bigson[root])continue;
		dfs1(v, root);
		dp[root][1] = max(dp[root][1], dp[v][0] + w);
	}
}

void dfs2(int root, int fa){
	for(int i = head[root];i;i = e[i].nextedge){
		int v = e[i].topoint, w = e[i].weight;
		if(v == fa)continue;
		if(v == bigson[root]){
			dp[v][2] = max(dp[root][1], dp[root][2]) + w;
		}
		else{
			dp[v][2] = max(dp[root][0], dp[root][2]) + w;
		}
		dfs2(v, root);
	}
}
signed main(){
    while(scanf("%d",&n) != -1){
        int w, v;
        tot = 0;
        memset(e,0,sizeof(e));
        memset(head,0,sizeof(head));
        memset(bigson,0,sizeof(bigson));
        memset(dp,0,sizeof(dp));
        for(int i = 2;i <= n;i++){
            v = read(); w = read();
            add(i,v,w); add(v,i,w);
        }
        dfs1(1,0);dfs2(1,0);
        for(int i = 1;i <= n;i++){
            printf("%d\n",max(dp[i][0],dp[i][2]));
        }
    }
    return 0;
}