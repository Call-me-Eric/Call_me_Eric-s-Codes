#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=700,Mod=998244353;

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

int n,m;
int f[Maxn+5][Maxn+5],h[Maxn+5][Maxn+5];

inline void Solve()
{
	memcpy(f,h,sizeof(h));
	For(i,1,n)
	{
		int p=i; For(j,i,n) if(f[j][i]) {p=j; break;}
		if(p>i) swap(f[i],f[p]); if(!f[i][i]) continue;
		p=Pow(f[i][i],Mod-2); For(j,1,n+1) f[i][j]=1ll*f[i][j]*p%Mod;
		For(j,i+1,n)
		{
			p=Mod-f[j][i];
			For(k,1,n+1) f[j][k]=(f[j][k]+1ll*f[i][k]*p)%Mod;
		}
	}
	Rof(i,n,1) if(f[i][i]) For(j,1,i-1)
	{
		int p=Mod-f[j][i];
		For(k,1,n+1) f[j][k]=(f[j][k]+1ll*f[i][k]*p)%Mod;
	}
	For(i,1,n)
	{
		int chk=1; For(j,1,n) chk&=(!f[i][j]);
		if(chk && f[i][n+1]) {printf("No\n"); return;}
	}
	For(i,1,n)
	{
		int chk=1; For(j,1,n) chk&=(!f[i][j]);
		if(chk) {printf("Many\n"); return;}
	}
	// For(i,1,n) {For(j,1,n+1) printf("%d ",f[i][j]); printf("\n");}
	For(i,1,n) printf("%d ",f[i][n+1]); printf("\n");
}
 
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);	
	
	n=read(),m=read();
	For(i,1,n) For(j,1,n+1) h[i][j]=read();
	Solve();
	while(m--)
	{
		int id=read();
		For(i,1,n+1) h[id][i]=read();
		Solve();
	}
	return 0;
} 
