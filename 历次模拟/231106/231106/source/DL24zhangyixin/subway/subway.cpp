#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1010;
int n,k,a[10][N],b[10][N],m,u,v,w,ans;
int dis[N][N],d[N][N],dd[N][N],sum[100010],num,aa,bb;
bool vis[N];
int r[N][N],s[N][N],t[N][N];
signed main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	scanf("%lld %lld",&n,&k);
	if(k==1){
		for(int i=1;i<=n;i++)
		 for(int j=1;j<=n;j++){
		 	if(i==j) dis[i][j]=0; 
		 	else dis[i][j]=0x3f3f3f3f3f3f3f3f;
		 }
		for(int i=1;i<=n;i++) scanf("%lld",&a[1][i]);
		for(int i=1;i<=n;i++) scanf("%lld",&b[1][i]);
		scanf("%lld",&m);
		for(int i=1;i<=m;i++){
			scanf("%lld %lld %lld",&u,&v,&w);
			dis[u][v]=dis[v][u]=w;
		}
		for(int p=1;p<=n;p++)
		 for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		  	dis[i][j]=min(dis[i][j],dis[i][p]+dis[p][j]);
		printf("%lld",dis[n]+a[1][1]+b[1][n]);
		return 0;
	}
	if(k==2){	
		num=0;ans=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;i++)
		 for(int j=1;j<=n;j++){
		 	if(i==j) dd[i][j]=0,d[i][j]=0; 
		 	else dd[i][j]=0x3f3f3f3f,d[i][j]=0x3f3f3f3f;
		 }
		for(int kk=1;kk<=k;kk++){
			for(int i=1;i<=n;i++) scanf("%lld",&a[kk][i]);
			for(int i=1;i<=n;i++) scanf("%lld",&b[kk][i]);
			scanf("%lld",&m);
			for(int i=1;i<=m;i++){
				if(kk==1){
					scanf("%lld %lld %lld",&u,&v,&w);d[u][v]=d[v][u]=w;
				}
				if(kk==2){
					scanf("%lld %lld %lld",&u,&v,&w);dd[u][v]=dd[v][u]=w;
				}
			}
		}
		for(int p=1;p<=n;p++)
		 for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++){
		  	d[i][j]=min(d[i][j],d[i][p]+d[p][j]);
		  	dd[i][j]=min(dd[i][j],dd[i][p]+dd[p][j]);
		  }
		sum[++num]=d[1][n]+a[1][1]+b[1][n];
		sum[++num]=dd[1][n]+a[2][1]+b[2][n];
		for(int i=2;i<=n;i++)
		sum[++num]=min(dd[1][i]+d[i][n]+a[2][1]+b[1][n]+b[2][i]+a[1][i],d[1][i]+dd[i][n]+a[1][1]+b[2][n]+b[1][i]+a[2][i]);
		for(int i=1;i<=num;i++) ans=min(ans,sum[i]);
		printf("%lld",ans); return 0;
	}
	if(k==3){
		num=0;ans=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;i++)
		 for(int j=1;j<=n;j++){
		 	if(i==j) r[i][j]=0,s[i][j]=0,t[i][j]=0; 
		 	else r[i][j]=0x3f3f3f3f3f3f3f3f,s[i][j]=0x3f3f3f3f3f3f3f3f,t[i][j]=0x3f3f3f3f3f3f3f3f;
		 }
		for(int kk=1;kk<=k;kk++){
			for(int i=1;i<=n;i++) scanf("%lld",&a[kk][i]);
			for(int i=1;i<=n;i++) scanf("%lld",&b[kk][i]);
			scanf("%lld",&m);
			for(int i=1;i<=m;i++){
				if(kk==1){
					scanf("%lld %lld %lld",&u,&v,&w);r[u][v]=r[v][u]=w;
				}
				if(kk==2){
					scanf("%lld %lld %lld",&u,&v,&w);s[u][v]=s[v][u]=w;
				}
				if(kk==3){
					scanf("%lld %lld %lld",&u,&v,&w);t[u][v]=t[v][u]=w;
				}
			}
		}
		for(int p=1;p<=n;p++)
		 for(int i=1;i<=n;i++)
		  for(int j=1;j<=n;j++)
		  {
		  	r[i][j]=min(r[i][j],r[i][p]+r[p][j]);
		  	s[i][j]=min(s[i][j],s[i][p]+s[p][j]);
		  	t[i][j]=min(t[i][j],t[i][p]+t[p][j]);
		  }
		  sum[++num]=r[1][n]+a[1][1]+b[1][n];
		sum[++num]=s[1][n]+a[2][1]+b[2][n];
		sum[++num]=t[1][n]+a[3][1]+b[3][n];
		for(int i=2;i<=n;i++)
		{
		sum[++num]=min(s[1][i]+r[i][n]+a[2][1]+b[1][n]+b[2][i]+a[1][i],r[1][i]+s[i][n]+a[1][1]+b[2][n]+b[1][i]+a[2][i]);
		sum[++num]=min(r[1][i]+t[i][n]+a[1][1]+b[3][n]+b[1][i]+a[3][i],t[1][i]+r[i][n]+a[3][1]+b[1][n]+b[3][i]+a[1][i]);
		sum[++num]=min(s[1][i]+t[i][n]+a[2][1]+b[3][n]+b[2][i]+a[3][i],t[1][i]+s[i][n]+a[3][1]+b[2][n]+b[3][i]+a[2][i]);
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				aa=a[1][1]+b[1][i]+a[2][i]+b[2][j]+a[3][j]+b[3][n];
				bb=a[3][1]+b[3][i]+a[2][i]+b[2][j]+a[1][j]+b[1][n];
				sum[++num]=min(s[1][i]+r[i][j]+t[j][n]+aa,t[1][i]+r[i][j]+s[j][n]+bb);
				aa=a[1][1]+b[1][i]+a[3][i]+b[3][j]+a[2][j]+b[2][n];
				bb=a[2][1]+b[2][i]+a[3][i]+b[3][j]+a[1][j]+b[1][n];
				sum[++num]=min(s[1][i]+t[i][j]+r[j][n]+aa,r[1][i]+t[i][j]+s[j][n]+bb);
				aa=a[2][1]+b[2][i]+a[1][i]+b[1][j]+a[3][j]+b[3][n];
				bb=a[3][1]+b[3][i]+a[1][i]+b[1][j]+a[2][j]+b[2][n];
				sum[++num]=min(s[1][i]+r[i][j]+t[j][n]+aa,t[1][i]+r[i][j]+s[j][n]+bb);
			}
		}
		for(int i=1;i<=num;i++)
		{
			ans=min(ans,sum[i]);
		 } 
		printf("%lld",ans);return 0;
	}
	return 0;
}
