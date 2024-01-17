#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
inline int read()
{
	int n=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		n=n*10+ch-'0';
		ch=getchar();
	}
	return n*f;
}
char s[100005];
int len;
int xl[100005];
int dp[100005][4][2][2];
int dp2[100005][15][2];
int zc;
int zzy[205][6];
//min(cnt6,4) min(cnt4,1) min(cnt9,2)
int dp3[100005][2];
int zf[6]={0,0,4,6,8,9};
int zf2[5]={0,0,4,6,8};
int solve()
{
	for(int i=1;i<=len+1;i++)
	{
		dp3[i][0]=dp3[i][1]=0;
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=1;k++)
			{
				dp[i][j][k][0]=dp[i][j][k][1]=0;
			}
		}
	}
	dp[len+1][0][0][1]=1;
	for(int i=len;i>=1;i--)
	{
		for(int j=0;j<=1;j++)
		{
			for(int k=0;k<=1;k++)
			{
				for(int pzt=0;pzt<=1;pzt++)
				{
					int nzt=pzt;
					int nj=j;
					if(j==1)nj++;
					if(xl[i]>0)nzt=0;
					dp[i][nj][k][nzt]=(dp[i][nj][k][nzt]+dp[i+1][j][k][pzt])%mod;
				}
			}
		}
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=0;k++)
			{
				for(int pzt=0;pzt<=1;pzt++)
				{
					if(pzt==1&&xl[i]<8)continue;
					int nzt=pzt;
					int nk=1;
					if(xl[i]>8)nzt=0;
					dp[i][j][nk][nzt]=(dp[i][j][nk][nzt]+dp[i+1][j][k][pzt])%mod;
				}
			}
		}
		for(int j=0;j<=0;j++)
		{
			for(int k=0;k<=0;k++)
			{
				for(int pzt=0;pzt<=1;pzt++)
				{
					if(pzt==1&&xl[i]<9)continue;
					int nzt=pzt;
					int nj=1;
					if(xl[i]>9)nzt=0;
					dp[i][nj][k][nzt]=(dp[i][nj][k][nzt]+dp[i+1][j][k][pzt])%mod;
				}
			}
		}
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=1;k++)
			{
				for(int pzt=0;pzt<=1;pzt++)
				{
					if(pzt==1&&xl[i]<1)continue;
					int nzt=pzt;
					if(xl[i]>1)nzt=0;
					dp3[i][nzt]=(dp3[i][nzt]+dp[i+1][j][k][pzt])%mod;
				}
			}
		}
		//printf("???%d %d\n",dp3[i][0],dp3[i][1]);
		for(int pzt=0;pzt<=1;pzt++)
		{
			for(int j=1;j<=4;j++)
			{
				if(pzt==1&&xl[i]<zf2[j])continue;
				int nzt=pzt;
				if(xl[i]>zf2[j])nzt=0;
				dp3[i][nzt]=(dp3[i][nzt]+dp3[i+1][pzt])%mod;
			}
		}
		//printf("???%d %d\n",dp3[i][0],dp3[i][1]);
	}
	int ans=0;
	ans=(ans+dp3[1][0])%mod;
	ans=(ans+dp3[1][1])%mod;
	//printf("%d\n",ans);
	for(int i=1;i<=len+1;i++)
	{
		for(int j=1;j<=14;j++)
		{
			for(int k=0;k<=1;k++)
			{
				dp2[i][j][k]=0;
			}
		}
	}
	dp2[len+1][zc][1]=1;
	for(int i=len;i>=1;i--)
	{
		for(int j=1;j<=14;j++)
		{
			for(int pzt=0;pzt<=1;pzt++)
			{
				if(dp2[i+1][j][pzt]==0)continue;
				for(int k=1;k<=5;k++)
				{
					if(pzt==1&&zf[k]>xl[i])continue;
					if(zzy[j][k]==-1)continue;
					int nzt=pzt;
					if(zf[k]<xl[i])nzt=0;
					dp2[i][zzy[j][k]][nzt]=(dp2[i][zzy[j][k]][nzt]+dp2[i+1][j][pzt])%mod;
				}
			}
		}
	}
	for(int j=1;j<=14;j++)ans=(ans+dp2[1][j][0])%mod;
	for(int j=1;j<=14;j++)ans=(ans+dp2[1][j][1])%mod;
	return ans;
}
int zy[560][6];
int now[560];
int fa[560],dy[560];
int findf(int n)
{
	if(fa[n]==n)return n;
	return fa[n]=findf(fa[n]);
}
bool vis[560];
void dfs(int x)
{
	if(x==-1)return;
	if(vis[x])return;
	vis[x]=true;
	for(int i=1;i<=5;i++)dfs(zy[x][i]);
}
//0,4,6,8,9
int findzt(int x1,int x2,int x3,int x4,int x5,int x6)
{
	int sth=x6;
	sth=sth*2+x5;
	sth=sth*2+x4;
	sth=sth*2+x3;
	sth=sth*7+x2;
	sth=sth*4+x1;
	return sth;
}
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout); 
	for(int i=0;i<=447;i++)
	{
		int sth=i;
		int ps6=sth%4;
		sth/=4;
		int pj0=sth%7;
		sth/=7;
		int pc4=sth%2;
		sth/=2;
		int pc9=sth%2;
		sth/=2;
		int pc60=sth%2;
		sth/=2;
		int pc64=sth;
		if(pj0!=6)pj0=max(pj0-1,0);
		if(ps6>=1)pc60=1;
		if(pc4)
		{
			zy[i][1]=448;
			continue;
		}
		if(pc9)pj0=0;
		zy[i][1]=findzt(ps6,pj0,pc4,pc9,pc60,pc64); 
	}
	for(int i=0;i<=447;i++)
	{
		int sth=i;
		int ps6=sth%4;
		sth/=4;
		int pj0=sth%7;
		sth/=7;
		int pc4=sth%2;
		sth/=2;
		int pc9=sth%2;
		sth/=2;
		int pc60=sth%2;
		sth/=2;
		int pc64=sth;
		if(pj0==0)
		{
			zy[i][2]=448;
			continue;
		}
		if(pc4)
		{
			zy[i][2]=448;
			continue;
		}
		if(ps6>=1)pc64=1;
		pc4=1;
		zy[i][2]=findzt(ps6,pj0,pc4,pc9,pc60,pc64); 
	}
	for(int i=0;i<=447;i++)
	{
		int sth=i;
		int ps6=sth%4;
		sth/=4;
		int pj0=sth%7;
		sth/=7;
		int pc4=sth%2;
		sth/=2;
		int pc9=sth%2;
		sth/=2;
		int pc60=sth%2;
		sth/=2;
		int pc64=sth;
		if(ps6==3)pj0=0;
		else pj0=min(pj0,5-ps6);
		if(pc60)pj0=0;
		if(pc64)
		{
			zy[i][3]=448;
			continue;
		}
		if(ps6>=2&&pc4&&pc9)
		{
			zy[i][3]=448;
			continue;
		}
		if(pc9)pj0=0;
		ps6=min(ps6+1,3);
		zy[i][3]=findzt(ps6,pj0,pc4,pc9,pc60,pc64); 
	}
	for(int i=0;i<=447;i++)
	{
		zy[i][4]=448;
	}
	for(int i=0;i<=447;i++)
	{
		int sth=i;
		int ps6=sth%4;
		sth/=4;
		int pj0=sth%7;
		sth/=7;
		int pc4=sth%2;
		sth/=2;
		int pc9=sth%2;
		sth/=2;
		int pc60=sth%2;
		sth/=2;
		int pc64=sth;
		if(pc4)
		{
			zy[i][5]=448;
			continue;
		}
		if(ps6>=1)pj0=0;
		if(pc9)pj0=0;
		pc9=1;
		zy[i][5]=findzt(ps6,pj0,pc4,pc9,pc60,pc64);
	}
	zy[448][1]=zy[448][2]=zy[448][3]=zy[448][4]=448;
	zy[448][5]=-1;
	//printf("???%d %d\n",findzt(0,6,0,0,0,0),zy[findzt(0,6,0,0,0,0)][1]);
	dfs(findzt(0,6,0,0,0,0));
	for(int i=0;i<=448;i++)if(!vis[i])zy[i][1]=zy[i][2]=zy[i][3]=zy[i][4]=448,zy[i][5]=-1;
	int sl=1;
	for(int i=0;i<=448;i++)now[i]=1;
	while(1)
	{
		int psl=sl;
		for(int i=0;i<=448;i++)fa[i]=i;
		for(int i=0;i<=448;i++)
		{
			for(int j=0;j<=i-1;j++)
			{
				bool flag=true;
				for(int k=1;k<=5;k++)
				{
					if(zy[i][k]==-1&&zy[j][k]==-1)continue;
					if(zy[i][k]==-1||zy[j][k]==-1)
					{
						flag=false;
						break;
					}
					if(now[zy[i][k]]!=now[zy[j][k]])
					{
						flag=false;
						break;
					}
				}
				if(flag==true)
				{
					fa[findf(i)]=findf(j);
					break;
				}
			}
		}
		sl=0;
		for(int i=0;i<=448;i++)if(fa[i]==i)dy[i]=++sl;
		for(int i=0;i<=448;i++)now[i]=dy[findf(i)];
		if(sl==psl)break;
	}
	//printf("%d %d\n",now[0],sl);
	for(int i=0;i<=448;i++)
	{
		for(int j=1;j<=5;j++)
		{
			if(zy[i][j]==-1)zzy[now[i]][j]=-1;
			else zzy[now[i]][j]=now[zy[i][j]];
		}
	}
	/*for(int i=1;i<=sl;i++)
	{
		for(int j=1;j<=5;j++)
		{
			printf("%d ",zzy[i][j]);
		}
		printf("\n");
	}*/
	zc=now[findzt(0,6,0,0,0,0)];
	//printf("%d\n",zc); 
	int t=read();
	for(int greg=1;greg<=t;greg++)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		for(int i=1;i<=len;i++)xl[i]=s[len-i+1]-'0';
		int now=1;
		while(xl[now]==0)
		{
			xl[now]=9;
			now++;
		}
		xl[now]--;
		if(now==len&&xl[now]==0)len--;
		int ansl=solve();
		scanf("%s",s+1);
		len=strlen(s+1);
		for(int i=1;i<=len;i++)xl[i]=s[len-i+1]-'0';
		int ansr=solve();
		//printf("%d %d\n",ansl,ansr);
		printf("%d\n",(ansr+mod-ansl)%mod);
	}
}
