#include <iostream>
#define ll long long
using namespace std;
const int mod=998244353,maxn=705;
int n,q,a[maxn][maxn],t[maxn][maxn],val[maxn],bel[maxn],res[maxn];
ll fpow(ll fa,ll fb)
{
	ll fans=1;
	while(fb) fans=(fb&1)?fans*fa%mod:fans,fa=fa*fa%mod,fb>>=1;
	return fans;
}
void solve()
{
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n+1;j++) t[i][j]=a[i][j];
		bel[i]=i;}
	for (int i=1;i<=n;i++)
	{
		int x=0,y=0;
		for (int j=i;j<=n;j++)
		{
			for (int k=i;k<=n;k++)
				if(t[j][k]){x=j,y=k;break;}
			if(x) break;
		}
		if(!x)
		{
			bool flag=0;
			for (int j=i;j<=n;j++) if(t[j][n+1]) flag=1;
			if(flag) cout<<"No"<<endl;
			else cout<<"Many"<<endl;
			return;
		}
		if(x!=i) for (int j=i;j<=n+1;j++) swap(t[i][j],t[x][j]);
		if(y!=i){for (int j=1;j<=n;j++) swap(t[j][i],t[j][y]);swap(bel[i],bel[y]);}
		int inv=fpow(t[i][i],mod-2);
		for (int j=i+1;j<=n;j++)
		{
			int fac=1ll*inv*t[j][i]%mod;
			for (int k=i;k<=n+1;k++) t[j][k]=(t[j][k]-1ll*t[i][k]*fac%mod+mod)%mod;
		}
	}
	for (int i=n;i;i--)
	{
		for (int j=i+1;j<=n;j++) t[i][n+1]=(t[i][n+1]-1ll*val[j]*t[i][j]%mod+mod)%mod;
		int inv=fpow(t[i][i],mod-2);
		val[i]=1ll*inv*t[i][n+1]%mod;
	}
	for (int i=1;i<=n;i++) res[bel[i]]=val[i];
	for (int i=1;i<=n;i++) cout<<res[i]<<" ";
	cout<<endl;
}
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	cin>>n>>q;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n+1;j++) cin>>a[i][j];
	solve();
	for (int i=1;i<=q;i++)
	{
		int x;cin>>x;
		for (int j=1;j<=n+1;j++) cin>>a[x][j];
		solve();
	}
	return 0;
}
