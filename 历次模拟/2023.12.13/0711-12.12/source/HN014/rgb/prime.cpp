#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const int maxn=1e5+10;

bool vis[maxn];
int prime[maxn],top;
bool Rejudge[maxn];
int Sta[6];
bool ccf;
inline void dfs(int now,int pre)
{
	if(ccf)return;
	if(pre&&!vis[pre])
	{
		ccf=true;
		return;
	}
	if(now==-1)return;
	dfs(now-1,pre);
	dfs(now-1,pre*10+Sta[now]);
}
inline void init(const int Lim=1e5)
{
	for(rg int i=2;i<=Lim;i+=1)
	{
		if(!vis[i])prime[++top]=i;
		for(rg int j=1;1ll*prime[j]*i<=Lim&&j<=top;j+=1)
		{
			vis[prime[j]*i]=true;
			if(i%prime[j]==0)break;
		}
	}
	vis[1]=true;
	for(rg int i=1;i<=Lim;i+=1)
		if(vis[i])
		{
			ccf=false;
			Sta[5]=i/100000;
			Sta[4]=(i/10000)%10;
			Sta[3]=(i/1000)%10;
			Sta[2]=(i/100)%10;
			Sta[1]=(i/10)%10;
			Sta[0]=i%10;
			dfs(5,0);
			if(!ccf)Rejudge[i]=true;
		}
}

int main()
{
	file("prime");
	init();
	int T;scanf("%d",&T);
	static int Pre[maxn];
	Pre[0]=0;
	for(rg int i=1;i<=(int)1e5;i+=1)
		Pre[i]=Pre[i-1]+(vis[i]==true&&Rejudge[i]);
	while(T--)
	{
		int l,r;scanf("%d %d",&l,&r);
		printf("%d\n",Pre[r]-Pre[l-1]);
	}
	return 0;
}
