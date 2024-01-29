#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=700,Maxk=2e3,Mod=998244353;

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
inline int Pow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod,y>>=1;
	}
	return res;
}

int n,m,s,cur,id[Maxn+5];
int h[Maxk+5][Maxn+5],g[Maxn+5],tim[Maxk+5];
int f[Maxn+5][Maxn+5],ans[Maxn+5][Maxn+5];
int vis[Maxn+5],dx[Maxn+5],typ[Maxn+5];
vector<int> t[Maxn*4+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void Insert(int nl,int nr,int l,int r,int p,int k)
{
	// cerr<<nl<<' '<<nr<<' '<<l<<' '<<r<<endl;
	if(l<=nl && nr<=r) {t[p].push_back(k); return;}
	int mid=(nl+nr)>>1;
	if(l<=mid) Insert(nl,mid,l,r,ls(p),k);
	if(r>mid) Insert(mid+1,nr,l,r,rs(p),k);
}
inline void Add(int x)
{
	dx[++s]=0,typ[s]=0;
	For(i,1,s-1) if(typ[i]) return;
	For(i,1,n+1) f[s][i]=h[x][i];
	For(i,1,s-1)
	{
		int p=Mod-f[s][dx[i]];
		For(j,1,n+1) f[s][j]=(f[s][j]+1ll*p*f[i][j])%Mod;
	}
	For(i,1,n) if(!vis[i] && f[s][i])
	{
		vis[i]=1,dx[s]=i; int p=Pow(f[s][i],Mod-2);
		For(j,1,n+1) f[s][j]=1ll*f[s][j]*p%Mod;
		break;
	}
	if(!dx[s]) typ[s]=(f[s][n+1]?1:2);
}
inline void Del() {int k=dx[s--]; vis[k]=0;}
inline void Solve(int id)
{
	For(i,1,n) if(typ[i]==1) {ans[id][0]=1; return;}
	For(i,1,n) if(typ[i]==2) {ans[id][0]=2; return;}
	For(i,1,n) g[i]=f[i][n+1];
	Rof(i,n,1)
	{
		int k=dx[i];
		For(j,1,i-1) f[j][n+1]=(f[j][n+1]+1ll*f[i][n+1]*(Mod-f[j][k]))%Mod;
	}
	For(i,1,n) ans[id][dx[i]]=f[i][n+1];
	For(i,1,n) f[i][n+1]=g[i];
}
inline void dfs(int l,int r,int p)
{
	int mid=(l+r)>>1;
	for(auto i:t[p]) Add(i);
	if(l==r) Solve(l);
	else dfs(l,mid,ls(p)),dfs(mid+1,r,rs(p));
	for(auto i:t[p]) Del();
}
 
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);	
	
	n=read(),m=read();
	For(i,1,n) For(j,1,n+1) h[i][j]=read();
	For(i,1,n) id[i]=i; cur=n;
	For(i,1,m)
	{
		int x=read(); ++cur;
		For(j,1,n+1) h[cur][j]=read();
		int k=id[x]; Insert(0,m,tim[k],i-1,1,k);
		id[x]=cur,tim[cur]=i;
	}
	For(i,1,n) Insert(0,m,tim[id[i]],m,1,id[i]);
	dfs(0,m,1);
	For(i,0,m)
	{
		if(ans[i][0]==1) {printf("No\n"); continue;}
		if(ans[i][0]==2) {printf("Many\n"); continue;}
		For(j,1,n-1) printf("%d ",ans[i][j]);
		printf("%d\n",ans[i][n]);
	}
	return 0;
} 
