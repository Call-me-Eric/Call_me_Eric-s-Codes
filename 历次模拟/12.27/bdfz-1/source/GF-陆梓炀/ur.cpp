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
ll n,k,pri[1000010],cnt=0,a[1000010],ans=0;
bl ck[1000010],pd[1000010];
struct sub{
	#define eps 1e-12
	map<pair<ll,ll>,pair<ll,ll> > mp;
	ll cnt1=0,cnt2=0;
	pair<pair<ll,ll>,pair<ll,ll> > p1[300030],p2[300030];
	void solve(){
		ll n1=n/2,n2=n-n1;
		db t=2*acos(-1.0)/n;
		fr(i,0,(1ll<<n1)-1){
			ll ppc=__builtin_popcount(i);
			if(ppc>k) continue;
			db sum1=0,sum2=0;
			fr(j,0,n1-1){
				if(i&(1ll<<j)){
					sum1+=cos(j*t);
					sum2+=sin(j*t);
				}
			}
			p1[++cnt1]=MP(MP(ppc,i),MP(round(sum1*100000000),round(sum2*100000000)));
		}
		fr(i,0,(1ll<<n2)-1){
			ll ppc=__builtin_popcount(i);
			if(ppc>k) continue;
			db sum1=0,sum2=0;
			fr(j,0,n2-1){
				if(i&(1ll<<j)){
					sum1+=cos((n1+j)*t);
					sum2+=sin((n1+j)*t);
				}
			}
			p2[++cnt2]=MP(MP(ppc,i),MP(-round(sum1*100000000),-round(sum2*100000000)));
		}
		sort(p1+1,p1+cnt1+1);
		sort(p2+1,p2+cnt2+1);
		ll now=0,res=0;
		pfr(i,cnt1,1){
			while(now<cnt2&&(p2[now+1].fir.fir+p1[i].fir.fir)<=k){
				now++;
				mp[p2[now].sec]=p2[now].fir;
			}
			if(mp.count(p1[i].sec)){
				if((p1[i].fir.fir+mp[p1[i].sec].fir)>ans){
					ans=p1[i].fir.fir+mp[p1[i].sec].fir;
					res=p1[i].fir.sec|(mp[p1[i].sec].sec<<n2);
				}
			}
		}
		fr(i,0,n-1) write((res>>i)&1);
	}
}sub;
void dfs(ll now,ll S){
	if(S>k) return;
	if(now==cnt){
		if(S<ans) return;
		fr(i,1,cnt){
			ll tmp=0,sum=0,maxx=0;
			fr(j,1,cnt){
				if(i!=j){
					tmp+=(a[j]/pri[i])*pri[j];
					sum+=(a[j]%pri[i])*pri[j];
					if(a[j]%pri[i]) maxx=max(maxx,pri[j]);
				} 
			}
			if((tmp+a[i]+max(maxx,(sum+pri[i]-1)/pri[i]))>n/pri[i]) return;
		}
		ans=max(ans,S);
		return;
	}
	now++;
	fr(i,0,(k-S)/pri[now]){
		a[now]=i;
		dfs(now,S+i*pri[now]);
	}
}
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read();
	k=read();
	ll tmp=n;
	for(ll i=2;i*i<=tmp;i++){
		if(tmp%i==0){
			pri[++cnt]=i;
			while(tmp%i==0) tmp/=i;
		}
	}
	if(tmp>1) pri[++cnt]=tmp;
	if(k==n){
		fr(i,1,n) write(1);
		return 0;
	}
	if(k<=1){
		fr(i,1,n) write(0);
		return 0;
	}
	if(cnt==1){
		fr(i,0,n-1) write((i%pri[1])<k/pri[1]);
		return 0;
	}
//	if(cnt==2){
//		ll p=pri[1],q=pri[2];
//		fr(i,0,k/p){
//			ll lim=min(min((k-i*p)/q,n/q-((i+q-1)/q)*p),((n/p-i)/q)*p);
//			ans=max(ans,i*p+lim*q);
//		}
//		fr(i,0,k/p){
//			ll lim=min(min((k-i*p)/q,n/q-((i+q-1)/q)*p),((n/p-i)/q)*p);
//			if(ans==(i*p+lim*q)){
//				ll tmpp=i/q;
//				fr(j,0,n-1){
//					if(ck[j]) continue;
//					if(!tmpp) break;
//					fr(x,0,p-1) fr(y,0,q-1) ck[j+(n/p)*x+(n/q)*y]=1;
//					tmpp--;
//				}
//				tmpp=i-(i/q)*q;
//				fr(j,0,n-1){
//					if(ck[j]) break;
//					fr(x,0,p-1) fr(y,0,tmpp-1) ck[j+(n/p)*x+(n/q)*y]=1;
//				}
//				break;
//			}
//		}
//		return 0;
//	}
	if(n<=36){
		sub.solve();
		return 0;
	}
}
