#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=2e6+10;
int n;
struct edge{
	int nt,to;
}e[N<<1];
int p[N],cnt;
inline void add(int x,int y){
	e[++cnt]={p[x],y};p[x]=cnt;
}
int a[N],dp[N][3];
void dfs(int x,int fa){
	int res=INT_MAX,son=1;
	for(int i=p[x];i;i=e[i].nt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,x);
		son=0;
		dp[x][2]=(dp[x][2]+min({dp[v][0],dp[v][1],dp[v][2]}));
		(dp[x][1]+=dp[v][1]);
		res=min(dp[v][2]-dp[v][1],res);
		(dp[x][0]+=dp[v][1]);
	}
	if(son){
		dp[x][1]=a[x];
		dp[x][2]=a[x];
		return ;
	}
	(dp[x][2]+=a[x]);
	(dp[x][1]+=res);
}
signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;i++)a[i]=rd();
	for(int i=1;i<n;i++){
		int u=rd(),v=rd();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	cout<<min(dp[1][2],dp[1][1]);
	return 0;
}

