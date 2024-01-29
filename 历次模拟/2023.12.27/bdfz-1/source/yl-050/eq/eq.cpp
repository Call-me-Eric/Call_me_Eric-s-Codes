#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int N=705;
const int mod=998244353;
const int inf=1e9;
#define ll long long
#define pb push_back
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}return res;
}
int n,m,a[N][N],A[N][N],xs[N][N],id[N];
inline void solve(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)A[i][j]=a[i][j];
	for(int i=1;i<=n;i++)id[i]=i;
	for(int i=1;i<=n;i++){
		int pos=i;
		for(int j=i+1;j<=n;j++)
			if(A[j][i]>A[pos][i])pos=j;
		swap(id[i],id[pos]);
		for(int j=1;j<=n+1;j++)
			swap(A[i][j],A[pos][j]);
		int inv=ksm(A[i][i],mod-2);
		for(int j=1;j<=n;j++)if(i^j){
			int kk=1ll*inv*A[j][i]%mod;
			for(int k=i;k<=n+1;k++)
				A[j][k]=(A[j][k]-1ll*A[i][k]*kk%mod+mod)%mod;
		}
	}int tag=0;
	for(int i=1;i<=n;i++)if(!A[i][i]){
		if(A[i][n+1])tag=2;
		else tag=max(tag,1);
	}if(tag)puts(tag==1?"Many":"No");
	else for(int i=1;i<=n;i++)
		printf("%d%c",1ll*ksm(A[i][i],mod-2)*A[i][n+1]%mod,i==n?'\n':' ');
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)a[i][j]=read();
	solve();while(m--){
		int id=read();
		for(int i=1;i<=n+1;i++)a[id][i]=read();
		solve();
	}
	return 0;
}
