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
	#define inf 8e18
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
ll n,m,a[2020],b[2020],c[4040],f[4040][2020],ans=0;
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	n=read();
	m=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n) b[i]=read();
	fr(i,1,n+m) c[i]=read();
	fr(i,1,n+m) fr(j,1,n) f[i][j]=-inf; 
	pfr(i,n,1){
		pfr(j,n,1) if(f[a[i]][j-1]!=-inf) f[a[i]][j]=max(f[a[i]][j],f[a[i]][j-1]+c[a[i]]-b[i]);
		ll tmp=n;
		fr(j,a[i],n+m-1){
			fr(k,0,tmp) if(f[j][k]!=-inf) f[j+1][k/2]=max(f[j+1][k/2],f[j][k]+(k/2)*c[j+1]);
			tmp/=2;
		}
	}
	fr(i,1,n+m) fr(j,0,1) ans=max(ans,f[i][j]);
	write(ans);
}
