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
ll r,g,b,n,m;
bl ck[100010];
struct node{
	ll u,v;
	char c;
}e[100010];
struct DSU{
	ll fa[255],res;
	il void init(){
		fr(i,1,n) fa[i]=i;
		res=n-1;
	}
	ll find(ll x){
		if(x==fa[x]) return x;
		return fa[x]=find(fa[x]);
	}
	il void merge(ll x,ll y){
		x=find(x);
		y=find(y);
		if(x==y) return;
		res--;
		fa[x]=y;
	}
}C[3],D[4];
il bl chk(ll u,ll v,char c){
	if(c=='r'){
		if(!r) return 0;
		r--;
	}
	else if(c=='g'){
		if(!g) return 0;
		g--;
	}
	else{
		if(!b) return 0;
		b--;
	}
	ll tmp1=D[1].res,tmp2=D[2].res,tmp3=D[3].res;
	ll lim1=D[0].res-1-C[0].res,lim2=D[0].res-1-C[1].res,lim3=D[0].res-1-C[2].res;
	if(D[1].find(u)!=D[1].find(v)) tmp1--;
	if(D[2].find(u)!=D[2].find(v)) tmp2--;
	if(D[3].find(u)!=D[3].find(v)) tmp3--;
	if(C[0].find(u)!=C[0].find(v)) lim1++;
	if(C[1].find(u)!=C[1].find(v)) lim2++;
	if(C[2].find(u)!=C[2].find(v)) lim3++;
	if(r>=tmp3&&g>=tmp2&&b>=tmp1&&r<=lim1&&g<=lim2&&b<=lim3) return 1;
	if(c=='r') r++;
	else if(c=='g') g++;
	else b++;
	return 0;
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	r=read();
	g=read();
	b=read();
	n=r+g+b+1;
	m=read();
	fr(i,1,m){
		e[i].u=read();
		e[i].v=read();
		cin>>e[i].c;
	}
	fr(i,0,2) C[i].init();
	fr(i,0,3) D[i].init();
	fr(i,1,m){
		if(e[i].c=='r'){
			C[0].merge(e[i].u,e[i].v);
			D[1].merge(e[i].u,e[i].v);
			D[2].merge(e[i].u,e[i].v);
		}
		else if(e[i].c=='g'){
			C[1].merge(e[i].u,e[i].v);
			D[1].merge(e[i].u,e[i].v);
			D[3].merge(e[i].u,e[i].v);
		}
		else{
			C[2].merge(e[i].u,e[i].v);
			D[2].merge(e[i].u,e[i].v);
			D[3].merge(e[i].u,e[i].v);
		}
	}
	fr(_,1,n-1){
		ll id=0;
		fr(i,1,m){
			if(ck[i]) continue;
			if(D[0].find(e[i].u)==D[0].find(e[i].v)) continue;
			if(chk(e[i].u,e[i].v,e[i].c)){
				id=i;
				break;
			}
		}
		if(!id){
			pf("NO");
			return 0;
		}
		ck[id]=1;
		fr(i,0,3) D[i].merge(e[id].u,e[id].v);
		fr(i,0,2) C[i].merge(e[id].u,e[id].v);
	}
	pf("YES\n");
	fr(i,1,m) write(ck[i]);
}
