#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	ll my_pow(ll a,ll b,ll mod){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res=(res*a)%mod;
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	ll qpow(ll a,ll b){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	#define db double
	#define pf printf
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define enter pc('\n')
	#define space pc(' ')
	#define fir first
	#define sec second
	#define MP make_pair
	#define il inline
	#define inf 1e18
	#define random(x) rand()*rand()%(x)
	#define inv(a,mod) my_pow((a),(mod-2),(mod))
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
	il void writesp(ll x){
		write(x);
		space;
	}
}
using namespace my_std;
ll n,m,q,a[1000010],fa[20],w[20][20];
ll f[1000010][20];
bl ck[1000010];
ll find(ll x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
il void merge(ll x,ll y,ll v){
	x=find(x);
	y=find(y);
	if(x==y) return;
	fr(i,0,19) fr(j,0,19) if(find(i)==x&&find(j)==y) w[i][j]=w[j][i]=v;
	fa[x]=y;
}
int main(){
	freopen("andgraph.in","r",stdin);
	freopen("andgraph.out","w",stdout);
	n=read();
	m=read();
	q=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n) ck[a[i]]=1;
	fr(i,0,19) fr(j,0,19) w[i][j]=inf;
	fr(i,0,19) w[i][i]=0;
	fr(i,0,19) fa[i]=i;
	fr(i,1,m){
		if(!ck[i]) continue;
		ll lst=-1;
		fr(j,0,19){
			if(!(i&(1ll<<j))) continue;
			if(lst!=-1) merge(lst,j,2*i);
			lst=j;
		}
	}
	fr(k,0,19) fr(i,0,19) fr(j,0,19) w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
	fr(i,0,m) fr(j,0,19) f[i][j]=inf;
	fr(i,1,m){
		ll id=0;
		fr(j,0,19) if(i&(1ll<<j)) id=j;
		ll x=i^(1ll<<id);
		fr(j,0,19) f[i][j]=min(f[x][j],w[id][j]);
	}
	while(q--){
		ll x=read(),y=read(),ans=inf;
		fr(i,0,19){
			if(!(a[y]&(1ll<<i))) continue;
			ans=min(ans,a[x]+a[y]+f[a[x]][i]);
		}
		if(ans==inf) writeln(-1);
		else writeln(ans);
	}
}
