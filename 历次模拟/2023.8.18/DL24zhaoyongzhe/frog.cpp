#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 5e4 + 10;
int pos[maxn][5], profit[maxn];
int n;
int ans[maxn];

int head[maxn], tot;
struct edge{
	int to ,nexte;
	edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn * 1000];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

void dfs(int u,int sum){
	ans[u] = max(ans[u],sum);
	for(int i = head[u];i;i = e[i].nexte){
		int v = e[i].to;
		if(ans[v] > sum + profit[v])continue;
		dfs(v,sum + profit[v]);
	}
}
signed main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= 5;j++)
			pos[i][j] = read();
		profit[i] = read();
	}
	for(int i = 1;i <= n;i++){
		for(int j = i + 1;j <= n;j++){
			bool flag = true;
			for(int k = 1;k <= 5;k++)
				if(pos[i][k] > pos[j][k]){
					flag = false;
					break;
				}
			if(flag){add(i,j);}
		}
	}
	for(int i = 1;i <= n;i++){add(0,i);}
	dfs(0,0);
	for(int i = 1;i <= n;i++)printf("%lld\n",ans[i]);
	return 0;
}

