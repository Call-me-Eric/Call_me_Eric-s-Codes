#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=(i1);i0<=(i2);++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=1e6+7;
int n;
struct Id{
	int v,nt;
}e[N<<1];
int p[N],id=1;
void add(int x,int y){e[++id]={y,p[x]};p[x]=id;}
int w[N];
int dp[N][3];
void dfs(int x,int ffa){
	dp[x][2]=w[x];
	dp[x][0]=dp[x][1]=0;
	
	int sum2=0,de=1ll<<40,sum3=0,flag=0;
	for(int i=p[x];i;i=e[i].nt){
		int v=e[i].v;if(v==ffa)continue;
		dfs(v,x);
		dp[x][2]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
		dp[x][0]+=min(dp[v][1],dp[v][2]);
		if(dp[v][1]<dp[v][2]){
			sum2+=dp[v][1];
			if(dp[v][2]-dp[v][1]<de){
				de=dp[v][2]-dp[v][1];
			}
		}
		else {
			sum2+=dp[v][2];
			flag=1;
		}
	}
//	if(de==(1ll<<40))de=0;

	dp[x][1]+=sum2+(flag?0:de);
//	cout<<x<<' '<<dp[x][0]<<" "<<dp[x][1]<<' '<<dp[x][2]<<'\n';
}
signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	n=rd();
	F(i,1,n)w[i]=rd();
	F(i,1,n-1){
		int x=rd(),y=rd();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	cout<<min(dp[1][0],min(dp[1][2],dp[1][1]));
	return 0;
}

