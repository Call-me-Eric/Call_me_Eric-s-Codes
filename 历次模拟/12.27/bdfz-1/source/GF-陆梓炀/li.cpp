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
ll n,m,head[200020],cnt=0,d[200020],tot[11];
bl ck[200020];
struct node{
	ll nxt,to;
}e[400040];
void add(ll u,ll v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs(ll u){
	ck[u]=1;
	tot[d[u]]++;
	go(u){
		ll v=e[i].to;
		if(!ck[v]) dfs(v);
	}
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read();
	m=read();
	fr(i,1,m){
		ll u=read(),v=read();
		add(u,v);
		add(v,u);
		d[u]++;
		d[v]++;
	}
	fr(i,1,n){
		if(d[i]>3){
			write(-1);
			return 0;
		} 
	}
	ll sum1=0,sum2=0;
	fr(i,1,n){
		if(ck[i]) continue;
		dfs(i);
		if(tot[0]==1&&!tot[1]&&!tot[2]&&!tot[3]) sum2++;
		else if(tot[1]==2&&!tot[0]&&!tot[3]) sum2+=(tot[1]+tot[2])*(tot[1]+tot[2]+1)/2;
		else if(!tot[0]&&!tot[1]&&!tot[3]) sum1+=tot[2];
		else if(tot[3]==1&&tot[1]==3&&!tot[0]&&!tot[2]) sum1+=3;
		else{
			write(-1);
			return 0;
		}
		tot[0]=tot[1]=tot[2]=tot[3]=0;
	}
	if(sum1) pf("1 %lld",sum1);
	else pf("0 %lld",sum2);
}
