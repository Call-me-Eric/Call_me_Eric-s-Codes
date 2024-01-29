#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using V=valarray<ll>;
const int mod=998244353;
ll inv(ll x){
	ll res=1,y=mod-2;
	for(;y;y>>=1,(x*=x)%=mod) if(y&1) (res*=x)%=mod;
	return res;
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	int n,q;
	cin>>n>>q;
	vector<V> a(n,V(n+1)),b(n,V(n+1)),c(n,V(n));
	vector<int> p(n);
	auto fix=[&](auto&v){
		for(ll&x:v) if((x=x%mod+mod)>=mod) x-=mod;
	};
	auto ins=[&](int i,int m){
		for(ll&x:a[i]) cin>>x;
		b[i]=a[i];p[i]=0;
		for(int j=0;j<n;j++) c[i][j]=i==j;
		for(int j=0;j<m;j++) if(i!=j&&p[j]<n){
			ll x=b[i][p[j]];
			if(x) fix(c[i]-=c[j]*x),fix(b[i]-=b[j]*x);
		}
		for(;!b[i][p[i]]&&p[i]<n;p[i]++);
		if(p[i]==n) return;
		ll iv=inv(b[i][p[i]]);
		fix(b[i]*=iv);fix(c[i]*=iv);
		for(int j=0;j<m;j++) if(i!=j){
			ll x=b[j][p[i]];
			if(x) fix(c[j]-=c[i]*x),fix(b[j]-=b[i]*x);
		}
	};
	for(int i=0;i<n;i++) ins(i,i);
	auto calc=[&](){
		int fl=0;
		for(int i=0;i<n;i++) if(p[i]==n) fl|=(b[i][n]?2:1);
		if(fl&2) cout<<"No";
		else if(fl) cout<<"Many";
		else{
			V v(n);
			for(int i=0;i<n;i++) v[p[i]]=b[i][n];
			for(ll&x:v) cout<<x<<" ";
		}
		cout<<"\n";
	};
	calc();
	for(int x;q--;ins(x,n),calc()){
		cin>>x;x--;
		if(p[x]==n) continue;
		ll&t=c[x][x],iv=inv(mod-t);
		if(t) fix(b[x]-=t*a[x]),t=0,fix(b[x]*=iv),fix(c[x]*=iv);
		fix(b[x]-=a[x]);t=mod-1;
		int g=n;
		for(int i=0;i<n;i++) if(x!=i){
			ll o=c[i][x];
			if(o) fix(b[i]+=b[x]*o),fix(c[i]+=c[x]*o);
			o=b[i][p[x]];
			if(p[i]<n||!o) continue;
			if(g==n){
				iv=inv(o);
				fix(c[i]*=iv);
				fix(b[i]*=iv);
				p[g=i]=p[x];
			}else fix(c[i]-=c[g]*o),fix(b[i]-=b[g]*o);
		}
	}
	return 0;
}