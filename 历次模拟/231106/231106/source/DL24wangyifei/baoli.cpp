#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
	long long xr=0,F=1; char cr;
	while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
	while(cr>='0'&&cr<='9') 
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
#define int long long
const int N=1e5+5,inf=2e15;
int n,t;
struct node {int x,w;} a[N];
il bool cmp(node x,node y) {return x.x<y.x;}
int f[2005][2005];
signed main()
{
//	freopen("ex_distanced2.in","r",stdin);
	n=read(),t=read();
	for(int i=1;i<=n;i++) a[i].x=read();
	for(int i=1;i<=n;i++) a[i].w=read();
	sort(a+1,a+n+1,cmp);
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0; a[0].x=-inf;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<i;k++)
			{
				if(a[i].x-a[k].x>t) f[i][j]=max(f[i][j],f[k][j-1]+a[i].w);
				else f[i][j]=max(f[i][j],f[k][j]+a[i].w);
			}
		}
	}
	int mx=0;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) f[n][j]=max(f[n][j],f[i][j]);
		
	for(int i=1;i<=n;i++) mx=max(mx,f[n][i]),cout<<mx<<" ";
	cout<<endl;
}
			
