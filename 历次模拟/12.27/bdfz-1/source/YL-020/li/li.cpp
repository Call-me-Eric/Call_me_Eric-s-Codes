#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int n,m,deg[Maxn+5],vis[Maxn+5];
int cnt,sum; ll K,B;
vector<int> v[Maxn+5],w;
inline void dfs(int x)
{
	vis[x]=1,cnt++,sum+=deg[x],w.push_back(x);
	for(auto y:v[x]) if(!vis[y]) dfs(y);
}

int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);	
	
	n=read(),m=read();
	For(i,1,m)
	{
		int a=read(),b=read();
		v[a].push_back(b),v[b].push_back(a);
		deg[a]++,deg[b]++;
	}
	For(i,1,n) if(deg[i]>3) {printf("-1\n"); return 0;}
	For(i,1,n) if(!vis[i])
	{
		cnt=0,sum=0,w.clear(),dfs(i);
		if(sum>cnt*2) {printf("-1\n"); return 0;}
		if(sum==cnt*2)
		{
			for(auto x:w) if(deg[x]>2) {printf("-1\n"); return 0;}
			K+=cnt,B+=cnt; continue;
		}
		int k=0;
		for(auto i:w) k+=(deg[i]==3);
		if(k>1) {printf("-1\n"); return 0;}
		if(k==1)
		{
			if(cnt!=4) {printf("-1\n"); return 0;}
			K+=3,B+=4;
		}
		else B+=1ll*cnt*(cnt+1)/2;
	}
	if(!K) printf("0 %lld\n",B);
	else printf("1 %lld\n",K);
	return 0;
} 
