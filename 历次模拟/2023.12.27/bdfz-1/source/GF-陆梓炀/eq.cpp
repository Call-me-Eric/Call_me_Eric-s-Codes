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
#define mod 998244353
ll n,q,A[770][770],ed[770],siz=0,nxt[770],maxx=0,ans[770];
struct node{
	ll id,nxt,a[770];
}p[1414];
il void ins(ll *a,ll t){
	fr(i,1,n){
		if(!a[i]) continue;
		if(ed[i]<t){
			if(!ed[i]) siz++;
			ll tmp=inv(a[i],mod);
			fr(j,i,n+1) a[j]=a[j]*tmp%mod;
			fr(j,i,n+1) swap(a[j],A[i][j]);
			swap(ed[i],t);
		}
		ll tmp=a[i];
		fr(j,i,n+1) a[j]=(a[j]-tmp*A[i][j]%mod+mod)%mod;
	}
	if(a[n+1]) maxx=max(maxx,t);
}
il void del(ll t){
	fr(i,1,n){
		if(ed[i]==t){
			siz--;
			ed[i]=0;
		}
	}
}
il void solve(ll t){
	if(t<maxx){
		pf("No\n");
		return;
	}
	if(siz<n){
		pf("Many\n");
		return;
	}
	pfr(i,n,1){
		ans[i]=A[i][n+1];
		fr(j,i+1,n) ans[i]=(ans[i]-A[i][j]*ans[j]%mod+mod)%mod;
	}
	fr(i,1,n){
		write(ans[i]);
		if(i<n) space;
	}
	enter;
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read();
	q=read();
	fr(i,1,n) fr(j,1,n+1) p[q+i].a[j]=read();
	fr(i,1,q){
		p[i].id=read();
		fr(j,1,n+1) p[i].a[j]=read();
	}
	fr(i,1,n) nxt[i]=q+1;
	pfr(i,q,1){
		p[i].nxt=nxt[p[i].id];
		nxt[p[i].id]=i;
	}
	fr(i,1,n) ins(p[q+i].a,nxt[i]);
	solve(0);
	fr(i,1,q){
		del(i);
		ins(p[i].a,p[i].nxt);
		solve(i);
	}
}
