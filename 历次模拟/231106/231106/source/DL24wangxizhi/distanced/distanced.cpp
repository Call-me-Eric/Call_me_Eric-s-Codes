#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10,inf=0x3f3f3f3f;
int n,ans[maxn],D;
int val[maxn],siz[maxn];
struct node{int p,a;}t[maxn];
struct DSU
{
	int fad[maxn];
	DSU(){iota(fad,fad+maxn,0);}
	inline int find(int x){return fad[x]==x?x:fad[x]=find(fad[x]);}
	inline void merge(int x,int y)
	{
		x=find(x),y=find(y);
		if(x==y) return;
		val[x]+=val[y],siz[x]+=siz[y],fad[y]=x; 
	}
}dsu;
namespace subtask1
{
	int vec[maxn];
	inline void dfs(int x,int sum,int cnt,int pre)
	{
		if(x>n) return ans[cnt]=max(ans[cnt],sum),void();
		if(abs(pre-t[x].p)>D) dfs(x+1,sum+t[x].a,cnt+1,t[x].p);
		else dfs(x+1,sum+t[x].a,cnt,t[x].p);
		dfs(x+1,sum,cnt,pre);
	}
	inline void solve()
	{
		dfs(1,0,0,-inf);
		for(int i=1;i<=n;i++) ans[i]=max(ans[i],ans[i-1]);
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<'\n';
	}
	
}
namespace subtask2
{

	inline void solve()
	{
		for(int i=1;i<=n;i++) val[i]=t[i].a,siz[i]=1;
		for(int i=2;i<=n;i++)
			if(abs(t[i-1].p-t[i].p)<=D) dsu.merge(i-1,i); 
		int tot=0;
		vector<int>vec;
		for(int i=1;i<=n;i++) if(dsu.fad[i]==i) vec.push_back(val[i]),tot+=val[i]; 
		sort(vec.begin(),vec.end(),greater<int>()); 
		ans[vec.size()]=tot;
		while(!vec.empty())
			tot-=vec.back(),vec.pop_back(),ans[vec.size()]=tot;
		for(int i=1;i<=n;i++)
			ans[i]=max(ans[i],ans[i-1]);
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";cout<<'\n';
	}
}
inline void solve()
{
	cin>>n>>D;
	for(int i=1;i<=n;i++) cin>>t[i].p;
	for(int i=1;i<=n;i++) cin>>t[i].a;
	sort(t+1,t+n+1,[](const node&A,const node&B){return A.p<B.p;}); 
	bool flag=true;
	for(int i=1;i<=n;i++) if(t[i].a<0) flag=false;
	if(flag) subtask2::solve();
	else subtask1::solve();
}
signed main()
{
	freopen("distanced.in","r",stdin);
	freopen("distanced.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
