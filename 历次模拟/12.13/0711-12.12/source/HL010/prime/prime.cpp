#include<cstdio>
#include<cstring>
#include<algorithm>
const int mod=998244353;
const int prime[]={
2,3,5,7,11,19,41,61,89,
109,449,499,881,991,6469,
6949,9049,9649,9949,
60649,666649,946669
};
using namespace std;
char s[100002];
int lv[100002],rv[100002],len;
int nw[100002];
void init(){
	int i;
	scanf("%s",s+1);
	int ll=strlen(s+1);
	for(i=1;i<=ll;i++)lv[i]=s[i]-'0';
	reverse(lv+1,lv+ll+1);
	lv[1]--;
	for(i=1;i<=ll;i++)if(lv[i]<0)lv[i]+=10,lv[i+1]--;
	scanf("%s",s+1);len=strlen(s+1);
	for(i=ll+1;i<=len;i++)lv[i]=0;
	for(i=1;i<=len;i++)rv[i]=s[i]-'0';
	reverse(rv+1,rv+len+1);
}
namespace dp_any{
	long long dp[100001];
	bool vis[100001];
	long long dfs(int x,bool lim){
		if(!x)return 1;
		if(!lim&&vis[x])return dp[x];
		int i,mx=lim?nw[x]:9;
		long long res=0;
		for(i=0;i<=mx;i+=2){
			if(i==2)continue;
			res+=dfs(x-1,lim&&(i==mx));
			res%=mod;
		}
		if(!lim)vis[x]=1,dp[x]=res;
		return res;
	}
	long long solve(){
		long long res=0;
		int i;
		for(i=1;i<=len;i++)nw[i]=rv[i];
		memset(vis,0,sizeof(vis));
		res+=dfs(len,1);
		memset(vis,0,sizeof(vis));
		for(i=1;i<=len;i++)nw[i]=lv[i];
		res+=mod-dfs(len,1);
		res%=mod;
		return res;
	}
}
namespace dp_1{
	const int sz[6]={0,1,4,6,8,9};
	long long dp[100001][2][2][2];
	bool vis[100001][2][2][2];
	long long dfs(int x,bool c1,bool c8,bool c9,bool lim){
		if(!x)return c1;
		if(!lim&&vis[x][c1][c8][c9])return dp[x][c1][c8][c9];
		int i,mx=lim?nw[x]:9;
		long long res=0;
		for(i=0;i<6;i++){
			int d=sz[i];
			if(d>mx)break;
			if(d==1&&c1)continue;
			if(d==8&&c8&&!c1)continue;
			if(d==9&&(c1||c8||c9))continue;
			if((d==4||d==6)&&!c1)continue;
			res+=dfs(x-1,c1||(d==1),c8||(d==8),c9||(d==9),lim&&(d==mx));
			res%=mod;
		}
		if(!lim)vis[x][c1][c8][c9]=1,dp[x][c1][c8][c9]=res;
		return res;
	}
	long long solve(){
		int i;
		long long res=0;
		for(i=1;i<=len;i++)nw[i]=rv[i];
		memset(vis,0,sizeof(vis));
		res+=dfs(len,0,0,0,1);
		for(i=1;i<=len;i++)nw[i]=lv[i];
		memset(vis,0,sizeof(vis));
		res+=mod-dfs(len,0,0,0,1);
		res%=mod;
		return res;
	}
}
namespace dp_9{
	const int sz[5]={0,4,6,8,9};
	long long dp[100001][2][2];
	bool vis[100001][2][2];
	long long dfs(int x,bool c48,bool c9,bool lim){
		if(!x)return c9;
		if(!lim&&vis[x][c48][c9])return dp[x][c48][c9];
		int i,mx=lim?nw[x]:9;
		long long res=0;
		for(i=0;i<5;i++){
			int d=sz[i];
			if(d>mx)break;
			if(d==4&&!c9)continue;
			if(d==9&&c48)continue;
			res+=dfs(x-1,c48||(d==4||d==8),c9||(d==9),lim&&(d==mx));
			res%=mod;
		}
		if(!lim)vis[x][c48][c9]=1,dp[x][c48][c9]=res;
		return res;
	}
	long long solve(){
		int i;
		long long res=0;
		for(i=1;i<=len;i++)nw[i]=rv[i];
		memset(vis,0,sizeof(vis));
		res+=dfs(len,0,0,1);
		for(i=1;i<=len;i++)nw[i]=lv[i];
		memset(vis,0,sizeof(vis));
		res+=mod-dfs(len,0,0,1);
		res%=mod;
		return res;
	}
}
namespace dp_49{
	const int sz[5]={0,4,6,8,9};
	long long dp[100001][4][3][2][2];
	bool vis[100001][4][3][2][2];
	long long dfs(int x,int u6,int st,bool h4,bool c0,bool lim){
		if(!x)return st==2;
		if(!lim&&vis[x][u6][st][h4][c0])return dp[x][u6][st][h4][c0];
		int i,mx=lim?nw[x]:9;
		long long res=0;
		for(i=0;i<5;i++){
			int d=sz[i];
			if(d>mx)break;
			if(d==0&&st==1)continue;
			if(d==9&&st!=1)continue;
			if(d==4&&st==1)continue;
			if(d==8&&st!=2)continue;
			if(d==6&&st==1&&!h4)continue;
			if(d==6&&st==0&&u6==3)continue;
			if(d==6&&u6&&c0)continue;
			int nst=st,nu6=u6+(d==6),xh0=c0;
			if(st==0&&d==4)nst++;
			if(st==1&&d==9)nst++;
			if(nst)nu6=0;
			if(d==0&&(st||u6))xh0=1;
			res+=dfs(x-1,nu6,nst,h4||(st==0&&!u6&&d==4),xh0,lim&&(d==mx));
			res%=mod;
		}
		if(!lim)vis[x][u6][st][h4][c0]=1,dp[x][u6][st][h4][c0]=res;
		return res;
	}
	long long solve(){
		int i;
		long long res=0;
		for(i=1;i<=len;i++)nw[i]=rv[i];
		memset(vis,0,sizeof(vis));
		res+=dfs(len,0,0,0,0,1);
		for(i=1;i<=len;i++)nw[i]=lv[i];
		memset(vis,0,sizeof(vis));
		res+=mod-dfs(len,0,0,0,0,1);
		res%=mod;
		return res;
	}
}
namespace dp_949{
	const int sz[5]={0,4,6,8,9};
	long long dp[100001][3][4];
	bool vis[100001][3][4];
	long long dfs(int x,int u6,int st,bool lim){
		if(!x)return st==3;
		if(!lim&&vis[x][u6][st])return dp[x][u6][st];
		int i,mx=lim?nw[x]:9;
		long long res=0;
		for(i=0;i<5;i++){
			int d=sz[i];
			if(d>mx)break;
			if(d==9&&st%2==1)continue;
			if(d==4&&st%2==0)continue;
			if(d==8&&st!=3)continue;
			if(d==6&&st<=1)continue;
			if(d==6&&st==2&&u6==2)continue;
			if(d==0&&st&&st<=2)continue;
			int nst=st,nu6=u6+(d==6);
			if(st==0&&d==9)nst++;
			if(st==1&&d==4)nst++;
			if(st==2&&d==9)nst++;
			if(nst==3)nu6=0;
			res+=dfs(x-1,nu6,nst,lim&&(d==mx));
			res%=mod;
		}
		if(!lim)vis[x][u6][st]=1,dp[x][u6][st]=res;
		return res;
	}
	long long solve(){
		int i;
		long long res=0;
		for(i=1;i<=len;i++)nw[i]=rv[i];
		memset(vis,0,sizeof(vis));
		res+=dfs(len,0,0,1);
		for(i=1;i<=len;i++)nw[i]=lv[i];
		memset(vis,0,sizeof(vis));
		res+=mod-dfs(len,0,0,1);
		res%=mod;
		return res;
	}
}
void solve(){
	init();
	long long res=0;
	res+=dp_any::solve();
	res+=dp_1::solve();
	res+=dp_9::solve();
	res+=dp_49::solve();
	res+=dp_949::solve();
	res%=mod;
	printf("%lld\n",res);
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)solve();
}
