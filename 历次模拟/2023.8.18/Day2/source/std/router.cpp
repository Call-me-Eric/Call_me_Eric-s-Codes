#include<bits/stdc++.h>
#define M 1000005
#define INF 100000000000000000
using namespace std;
inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) f |= (c == '-');
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}
struct E{
	int to,nx;
}edge[M<<1];
int tot,head[M];
void Addedge(int a,int b){
	edge[++tot].to=b;
	edge[tot].nx=head[a];
	head[a]=tot;
}
long long dp[M][3];
int fa[M];
int A[M];
inline void Add(long long &x,long long y){
	x+=y;
	if(x>=INF)x=INF;
}
void dfs(int now){
	dp[now][0]=dp[now][1]=dp[now][2]=0;
	dp[now][1]=A[now];dp[now][2]=INF;
	for(int i=head[now];i;i=edge[i].nx){
		int nxt=edge[i].to;
		if(nxt==fa[now])continue;
		fa[nxt]=now;
		dfs(nxt);
		dp[now][2]=min(dp[now][2]+min(dp[nxt][1],dp[nxt][2]),dp[now][0]+dp[nxt][1]);
		Add(dp[now][1],min(dp[nxt][0],min(dp[nxt][1],dp[nxt][2])));
		Add(dp[now][0],dp[nxt][2]);
	}
}
int main(){
    freopen("router.in", "r", stdin);
    freopen("router.out", "w", stdout);
	int n=rd();
	memset(head,0,sizeof(head));
	tot=0;for(int i=1;i<=n;i++)head[i]=0;
	for(int i=1;i<=n;i++) A[i]=rd();
	for(int i=1;i<n;i++){
		int a=rd(),b=rd();
		Addedge(a,b);
		Addedge(b,a);
	}
	dfs(1);
	long long ans=min(dp[1][1],dp[1][2]);
	printf("%lld\n",ans);
	return 0;
}
