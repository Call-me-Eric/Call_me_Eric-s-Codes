#include<bits/stdc++.h>
using namespace std;
#define N 702
#define ll long long
const int p=998244353;
int n,q,i,j,k,z,x,a[N][N],s[N][N],b[N][N],f[N];
ll ksm(ll x,ll k){
	if(!k) return 1;
	ll t=ksm(x,k>>1);
	if(k&1) return t*t%p*x%p;
	return t*t%p;
}
int ans[N],flg[N];
void solv(){
	bool flg1=0,flg2=0;
	for(i=n;i;i--){
		int s=0,flg3=0;
		for(j=1;j<=n;j++) s=(s+1ll*b[i][j]*f[j])%p;
		for(j=i+1;j<=n;j++) s=(s-1ll*ans[j]*a[i][j])%p,flg3|=a[i][j]&&flg[j];
		if(!a[i][i])
			flg1=1,flg2|=s&&!flg3,flg[i]=1;
		else flg[i]=0;
		ans[i]=ksm((a[i][i]+p)%p,p-2)*((s+p)%p)%p;
		flg[i]|=flg3;
	}
	if(flg1) printf(flg2?"No":"Many");
	else for(i=1;i<=n;i++) printf("%d ",ans[i]);
	puts("");
}
mt19937 gen(time(0));
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;b[i][i]=1,scanf("%d",&f[i]),i++)
		for(j=1;j<=n;j++) scanf("%d",&a[i][j]),s[i][j]=a[i][j];
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(a[j][i])
				if(!a[i][i])
					for(k=1;k<=n;k++)
						swap(a[i][k],a[j][k]),swap(b[i][k],b[j][k]);
				else{
					for(k=n;k;k--)
						b[j][k]=(1ll*b[j][k]*a[i][i]-1ll*b[i][k]*a[j][i])%p;
					for(k=i+1;k<=n;k++)
						a[j][k]=(1ll*a[j][k]*a[i][i]-1ll*a[i][k]*a[j][i])%p;
					a[j][i]=0;
				}
	solv();
	while(q--){
		scanf("%d",&z);
		x=-1;
		for(i=n;i;i--)
			if(b[i][z]){
				for(j=i-1;j;j--)
					if(b[j][z]){
						for(k=j;k<=n;k++)
							a[j][k]=(1ll*a[j][k]*b[i][z]-1ll*a[i][k]*b[j][z])%p;
						for(k=1;k<=n;k++)
							if(k^z)
							b[j][k]=(1ll*b[j][k]*b[i][z]-1ll*b[i][k]*b[j][z])%p;
						b[j][z]=0;
					}
				x=i;
				break;
			}
		for(i=1;i<=n;i++) scanf("%d",&s[z][i]);
		scanf("%d",&f[z]);
		if(~x){
			memset(a[x],0,sizeof(a[x]));
			for(i=1;i<=n;i++)
				for(b[x][i]=gen()%(p-1)+1,j=1;j<=n;j++)
					a[x][j]=(a[x][j]+1ll*s[i][j]*b[x][i])%p;
		}
		memset(a[z],0,sizeof(a[z]));
		for(i=1;i<=n;i++)
			for(b[z][i]=gen()%(p-1)+1,j=1;j<=n;j++)
				a[z][j]=(a[z][j]+1ll*s[i][j]*b[z][i])%p;
		for(i=1;i<=n;i++)
			if(i==x||i==z){
				for(j=1;j<i;j++)
					if(a[i][j])
						if(!a[j][j])
							for(k=1;k<=n;k++)
								swap(a[i][k],a[j][k]),swap(b[i][k],b[j][k]);
						else{
							for(k=1;k<=n;k++)
								b[i][k]=(1ll*b[i][k]*a[j][j]-1ll*b[j][k]*a[i][j])%p;
							for(k=j+1;k<=n;k++)
								a[i][k]=(1ll*a[i][k]*a[j][j]-1ll*a[j][k]*a[i][j])%p;
							a[i][j]=0;
						}
			}
		solv();
	}
	return 0;
}
