#include<bits/stdc++.h>
using namespace std;
int n,k,sum,s1;
vector<int>v,kx;
unordered_map<int,unordered_map<int,unordered_map<int,int> > >mp;
int dfs(int xs,int k1,int dep)
{
	if(dep==s1+1||k1==kx.size())return xs;
	if(mp[xs][k1].count(dep))return mp[xs][k1][dep];
	int &t=mp[xs][k1][dep];
	t=1e9;
	if(xs>=kx[k1])t=min(t,dfs(xs-kx[k1],k1,dep+1));
	if(xs<kx[k1]||k1<(int)kx.size()-1)t=min(t,dfs(xs,k1+1,dep));
	return t;
}
bool vis[1000001];
vector<int>v2;
int las[1000001];
void hy(int xs,int k1,int dep)
{
	if(dep==s1+1||k1==kx.size())
	{
		for(int i=0;i<(int)v2.size();++i)
		{
			for(int j=0;j<las[kx[v2[i]]];++j)
				for(int k=i+s1*j;k<n;k+=n/(kx[v2[i]]/las[kx[v2[i]]]))
					vis[k]=1;
		}
		for(int i=0;i<n;++i)
			printf("%d",vis[i]);
		exit(0);
	}
	if(xs>=kx[k1]&&dfs(xs-kx[k1],k1,dep+1)==mp[xs][k1][dep])
	{
		v2.push_back(k1);
		hy(xs-kx[k1],k1,dep+1);
	}
	hy(xs,k1+1,dep);
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(n==k)
	{
		for(int i=1;i<=n;++i)printf("1");
		return 0;
	}
	int n1=n;
	sum=1,s1=1;
	for(int i=2;i<=n;++i)
		if(n1%i==0)
		{
			sum*=i;
			while(n1%i==0)
			{
				n1/=i;
				s1*=i;
			}
			s1/=i;
		}
	for(int i=1;i<sum;++i)
		if(sum%i==0)
		{
			for(int j=1;j<=i;++j)
				if(!las[j*(sum/i)])
				{
					las[j*(sum/i)]=j;
					kx.push_back(j*(sum/i));
				}
		}
	kx.push_back(sum);
	dfs(k,0,1);
	hy(k,0,1);
	return 0;
} 
