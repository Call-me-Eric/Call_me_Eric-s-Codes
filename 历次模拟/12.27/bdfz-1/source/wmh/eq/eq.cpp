#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int powdv(int x,int y=mod-2){
	int ans=1;
	while(y){
		if(y&1)ans=1ll*ans*x%mod;
		y>>=1,x=1ll*x*x%mod;
	}
	return ans;
}
int n,q;
int a[705];
vector<int>vc[1405];
int wL[1405],wR[1405],ls[705];
vector<int>jj[2805];
void jiaru(int l,int r,int o,int ll,int rr,int x){
	if(l>=ll&&r<=rr){
		jj[o].emplace_back(x);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=ll)jiaru(l,mid,o<<1,ll,rr,x);
	if(mid<rr)jiaru(mid+1,r,o<<1|1,ll,rr,x);
}
struct gaosi{
	vector<vector<int>>g;
	vector<int>gg;
	void poo(){
		g.pop_back();gg.pop_back();
	}
	int jia(vector<int>v){
		int sz=gg.size();
		for(int i=0;i<sz;++i)if(gg[i]){
			int wz=gg[i],hh=mod-v[wz];
			if(!hh)continue;
			for(int j=0;j<=n;++j)if(g[i][j])
				v[j]=(v[j]+1ll*g[i][j]*hh)%mod;
		}
		int ww=0;
		for(int i=1;i<=n;++i)if(v[i]){
			ww=i;
			break;
		}
		if(!ww){
			g.emplace_back(v);
			gg.emplace_back(0);
			return (v[0]==0);
		}
		int ny=powdv(v[ww]);
		for(int i=0;i<=n;++i)v[i]=1ll*v[i]*ny%mod;
		g.emplace_back(v);gg.emplace_back(ww);
		return -1;
	}
	void jiej(){
		if((signed)gg.size()<n){
			puts("Many");
			return;
		}
		for(auto cu:gg)if(cu==0){
			puts("Many");
			return;
		}
		vector<int>x(n+1);
		for(int i=n-1;i>=0;--i){
			int wz=gg[i];
			int he=g[i][0];
			for(int j=i+1;j<n;++j)he=(he-1ll*g[i][gg[j]]*x[gg[j]])%mod;
			x[wz]=(he+mod)%mod;
		}
		for(int i=1;i<=n;++i)printf("%d",x[i]),putchar(i==n?'\n':' ');
	}
}st;
void solve(int l,int r,int o){
	int ys=st.gg.size();
	int fl=1;
	for(auto cu:jj[o]){
		int zz=st.jia(vc[cu]);
		if(zz==1){
			fl=0;
			break;
		}
	}
	if(!fl){
		for(int i=l;i<=r;++i)puts("No");
		while((signed)st.gg.size()>ys)st.poo();
		return;
	}
	if(l==r){
		st.jiej();
		while((signed)st.gg.size()>ys)st.poo();
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid,o<<1),solve(mid+1,r,o<<1|1);
	while((signed)st.gg.size()>ys)st.poo();
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)scanf("%d",&a[j]);
		scanf("%d",&a[0]);
		vector<int>vv;
		for(int j=0;j<=n;++j)vv.emplace_back(a[j]);
		ls[i]=i;
		vc[i]=vv,wL[i]=0,wR[i]=q;
	}
	for(int i=1;i<=q;++i){
		int z;
		scanf("%d",&z);
		int sl=ls[z];
		for(int j=1;j<=n;++j)scanf("%d",&a[j]);
		scanf("%d",&a[0]);
		vector<int>vv;
		for(int j=0;j<=n;++j)vv.emplace_back(a[j]);
		vc[n+i]=vv;
		wR[sl]=i-1;wL[n+i]=i,wR[n+i]=q;
		ls[z]=n+i;
	}
	for(int i=1;i<=n+q;++i)jiaru(0,q,1,wL[i],wR[i],i);
	solve(0,q,1);
	return 0;
}
