#include <bits/stdc++.h>
using namespace std;
const int N=705,mod=998244353;
int qpow(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%mod; 
		a=1ll*a*a%mod; b>>=1;
	}
	return ans;
}
int n,q;
struct Vector{
	int t,a[N];
	Vector(){
		t=-1;
		memset(a,0,sizeof a);
	}
	void readin(int _t){t=_t;for(int i=1; i<=n+1; i++) scanf("%d",&a[i]);}
	int &operator[](const int x){return a[x];}
	void getnew(Vector& cur,int fr){
		int inv=1ll*a[fr]*qpow(cur[fr])%mod;
		for(int i=fr; i<=n+1; i++)
			cur[i]=(1ll*cur[i]*inv-a[i]+mod)%mod;
	}
}base[N];
int Not=-1;
void insert(Vector cur){
	for(int i=1; i<=n; i++) if(cur[i]){
		if(cur.t>base[i].t) swap(cur,base[i]);
		base[i].getnew(cur,i);
	}
	if(cur[n+1]) Not=max(Not,cur.t);
}
int ans[N];
void printans(){
	for(int i=n; i; i--){
		int val=base[i][n+1];
		for(int j=i+1; j<=n; j++) val=(val-1ll*base[i][j]*ans[j]%mod+mod)%mod;
		ans[i]=1ll*val*qpow(base[i][i])%mod;
	}
	for(int i=1; i<=n; i++) printf("%d ",ans[i]);
	puts("");
}
vector <pair <int,Vector> > vec[N]; 

int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; i++){
		Vector cur; cur.readin(0);
		vec[i].emplace_back(0,cur);
	}
	for(int i=1; i<=q; i++){
		Vector cur; int id;
		scanf("%d",&id);
		cur.readin(i);
		vec[id].emplace_back(i,cur);
	}
	for(int i=1; i<=n; i++) reverse(vec[i].begin(),vec[i].end());
	for(int i=0; i<=q; i++){
		for(int j=1; j<=n; j++) if(vec[j].size()&&vec[j].back().first==i){
			auto cur=vec[j].back().second;
			vec[j].pop_back();
			int t=vec[j].empty()?n:vec[j].back().first-1;
			cur.t=t;
			insert(cur);
		}
		// for(int i=1; i<=n; i++,puts("")) 
		// 	for(int j=1; j<=n+1; j++) printf("%d ",base[i][j]);
		if(Not>=i) puts("No");
		else{
			auto chk = [&](){
				for(int j=1; j<=n; j++) if(base[j].t<i)
					return 0;
				return 1;
			};
			if(!chk()) puts("Many");
			else
				printans();
		}
	}
	return 0;
}