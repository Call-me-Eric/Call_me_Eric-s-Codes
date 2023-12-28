#include<bits/stdc++.h>
using namespace std;
int n,m,u[200001],v[200001];
vector<int>nxt[200001];
void check1()
{
	for(int i=1;i<=n;++i)
		if(nxt[i].size()>=4)
		{
			printf("-1"); 
			exit(0);
		}
	for(int i=1;i<=n;++i)
		if(nxt[i].size()>=3)
		{
			if(nxt[nxt[i][0]].size()!=1||
				nxt[nxt[i][1]].size()!=1||
				nxt[nxt[i][2]].size()!=1)
			{
				printf("-1");
				exit(0);
			}
		}
}
bool vis[2000001];
int dfs1(int x)
{
	vis[x]=1;
	int cnt=0,ans=0;
	for(int j:nxt[x])
		if(!vis[j])ans+=dfs1(j);
		else ++cnt;
	if(cnt>=2)return 1;
	else return ans?(ans+1):ans;
}
int dfs2(int x)
{
	vis[x]=1;
	int cnt=0,ans=1;
	for(int j:nxt[x])
		if(!vis[j])ans+=dfs2(j);
	return ans;
}
void check2()
{
	int sum=0;
	for(int i=1;i<=n;++i)
		if(nxt[i].size()==3)
			sum+=3;
	for(int i=1;i<=n;++i)
		if(!vis[i])sum+=dfs1(i);
	if(sum)
	{
		printf("%d %d",1,sum);
		exit(0);
	}
}
void check3()
{
	memset(vis,0,sizeof vis);
	long long ans=0;
	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			int t=dfs2(i);
			ans+=1ll*t*(t+1)/2;
		}
	printf("0 %lld",ans);
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",u+i,v+i);
		nxt[u[i]].push_back(v[i]);
		nxt[v[i]].push_back(u[i]);
	}
	check1();
	check2();
	check3();
	return 0;
}
