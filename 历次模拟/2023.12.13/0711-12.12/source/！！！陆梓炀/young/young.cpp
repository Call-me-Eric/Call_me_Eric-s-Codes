#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll int
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
ll n,q,k;
struct node{
	ll a[33];
}A,B;
map<node,ll> f,g;
il bl operator<(const node &x,const node &y){
	fr(i,1,30) if(x.a[i]!=y.a[i]) return x.a[i]<y.a[i];
	return 0;
}
il bl operator==(const node &x,const node &y){
	fr(i,1,30) if(x.a[i]!=y.a[i]) return 0;
	return 1;
}
il void inc(ll &x,ll y){
	((x+=y)>=mod)?(x-=mod):0;
}
int main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	n=read();
	fr(i,1,n) A.a[i]=read();
	n=read();
	fr(i,1,n) B.a[i]=read();
	q=read();
	k=read();
	f[A]=1;
	fr(_,1,k){
		g.clear();
		for(map<node,ll>::iterator it=f.begin();it!=f.end();it++){
			node u=(*it).fir;
			ll val=(*it).sec;
			fr(i,1,30){
				if(i==1||u.a[i-1]>u.a[i]){
					u.a[i]++;
					inc(g[u],val);
					u.a[i]--;
				}
				if(u.a[i]&&(i==30||u.a[i+1]<u.a[i])){
					u.a[i]--;
					inc(g[u],val);
					u.a[i]++;
				}
			}
		}
		swap(f,g);
	}
	write(f[B]);
}
/*
8
5 4 3 3 2 1 1 1
6
7 4 4 2 2 1
1
20
*/
