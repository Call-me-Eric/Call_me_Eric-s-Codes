#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int mod=998244353;
char s[N];int T,a[N],n,pw[N],dp[N][2][2],sum[N],sum2[N];
void Inc(int &a,int b){a+=b;if(a>=mod)a-=mod;}
int dfs(int nw,bool up,bool zero)
{
	if(nw==n+1)return !zero;
	if(~dp[nw][up][zero])return dp[nw][up][zero];
	int &res=dp[nw][up][zero];res=0;int mx=up?a[nw]:9;
	for(auto yl:{0,4,6,8})if(yl<=mx)Inc(res,dfs(nw+1,up&&yl==mx,zero&&yl==0));
	if(zero)
	{
		if(mx>=8)
		{
			if(mx==8&&up)
			{
				bool flag=0;
				for(int j=nw+1;j<=n;++j)
				{
					int tmp=a[j];
					if(!flag&&tmp==1){Inc(res,dfs(j+1,1,0));flag=1;continue;}
					if(flag||tmp>1){Inc(res,sum[n-j]);break;}
				}	
			}
			else if(n-nw-1>=0)Inc(res,sum[n-nw-1]);
		}
		if(mx>=1)Inc(res,dfs(nw+1,mx==1&&up,0));
		if(mx>=4)
		{
			if(!up||mx>4){if(n-nw-1>=0)Inc(res,sum[n-nw-1]);}
			else
			{
				bool flag=0;
				for(int j=nw+1;j<=n;++j)
				{
					if(a[j]==9)Inc(res,dfs(j+1,1,0));
					if(a[j]>6){Inc(res,sum[n-j-1]);break;}
					if(a[j]<6)break;
				}
			}
		}
		if(mx>=6)
		{
			if(!up||mx>6){Inc(res,sum2[n-nw]);}
			else
			{
				for(int j=nw+1;j<=n;++j)
				{
					for(auto i:{0,6,9})if(a[j]>i)Inc(res,sum2[n-j]);
					if(a[j]!=0&&a[j]!=6&&a[j]!=9)break;if(j==n)Inc(res,a[j]==9);
				}
			}
		}
		if(mx==9)
		{
			if(!up){Inc(res,sum2[n-nw]);}
			else
			{
				for(int j=nw+1;j<=n;++j)
				{
					for(auto i:{0,6,9})if(a[j]>i)Inc(res,sum2[n-j]);
					if(a[j]!=0&&a[j]!=6&&a[j]!=9)break;if(j==n)Inc(res,a[j]==9);
				}
			}
		}
		auto fuck=[&](int num,int len)
		{
			if(len+nw-1<=n)
			{
				if(!up)Inc(res,pw[n-(nw+len-1)]);
				else
				{
					int tmp=0;
					for(int i=1;i<=len;++i)tmp=tmp*10+a[nw+i-1];
					if(num==tmp)Inc(res,dfs(nw+len,1,0));
					else if(num<tmp)Inc(res,pw[n-(nw+len-1)]);				
				}	
			}
		};
		fuck(9,1);fuck(91,2);fuck(981,3);fuck(901,3);fuck(9801,4);fuck(9081,4);fuck(649,3);fuck(949,3);fuck(9469,4);
		fuck(6049,4);fuck(6649,4);fuck(66649,5);fuck(60049,5);fuck(66049,5);fuck(94669,5);
		fuck(600049,6);fuck(660049,6);fuck(6660049,7);fuck(6000049,7);fuck(666049,6);fuck(6666049,7);
	}
	return res;
}
int solve(bool type)
{
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;++i)a[i]=s[n-i+1]-'0';
	if(type){--a[1];int nw=1;while(a[nw]<0){a[nw]+=10;a[nw+1]--;++nw;}}
	if(a[n]==0)--n;if(!n)return 0;reverse(a+1,a+n+1);memset(dp,-1,sizeof(dp));return dfs(1,1,1);
}
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	pw[0]=sum[0]=1;sum2[0]=0;
	for(int i=1;i<N;++i)pw[i]=4ll*pw[i-1]%mod;
	for(int i=1;i<N;++i)sum[i]=(sum[i-1]+pw[i])%mod;
	for(int i=1;i<N;++i)sum2[i]=(sum2[i-1]*3ll+pw[i-1])%mod;
	scanf("%d",&T);
	while(T--)
	{
		int L=solve(1),R=solve(0);
		printf("%d\n",(R-L+mod)%mod);
	}
	return 0;
}
