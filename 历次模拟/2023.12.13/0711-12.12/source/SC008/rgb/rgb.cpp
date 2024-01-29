#include <bits/stdc++.h>
using namespace std;
int mp[256];
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.ot","w",stdout);
	cin.tie(0)->sync_with_stdio(0);
	auto fuck=[&](){
		cout<<"NO";
		exit(0);
	};
	mp['g']=1;mp['b']=2;
	int r,g,b,n,m,k=0;
	cin>>r>>g>>b>>m;
	n=r+g+b+1;
	vector<int> lst,lo,fa(n),u(m),v(m),c(m),o(m);
	iota(begin(fa),end(fa),0);
	auto getf=[&](int x){
		while(x!=fa[x]) x=fa[x]=fa[fa[x]];
		return x;
	};
	auto merge=[&](int x,int y){
		if((x=getf(x))==(y=getf(y))) return 0;
		fa[x]=y;
		return 1;
	};
	for(int i=0;i<m;i++){
		char x;
		cin>>u[i]>>v[i]>>x;
		c[i]=mp[x];
		u[i]--;v[i]--;
		k+=merge(u[i],v[i]);
	}
	if(k!=n-1) fuck();
	iota(begin(fa),end(fa),k=0);
	for(int i=0;i<m;i++) if(c[i]==2) k+=merge(u[i],v[i]);
	if(k<b) fuck();
	auto shit=[&](int op){
		lst=fa;
		for(int i=0;i<m;i++) if(!c[i]) merge(u[i],v[i]);
		for(int i=0;i<m;i++) if(c[i]==1&&(op||g)&&merge(u[i],v[i])) o[i]=1,g--;
		fa=lst;
		for(int i=0;i<m;i++) if(c[i]==1) merge(u[i],v[i]);
		for(int i=0;i<m;i++) if(!c[i]&&(op||r)&&merge(u[i],v[i])) o[i]=1,r--;
		if(g<0||r<0) fuck();
		fa=lst;
		for(int i=0;i<m;i++) if(o[i]) k+=merge(u[i],v[i]);
		if(!op) for(int i=0;i<m;i++){
			if(r&&!c[i]&&merge(u[i],v[i])) r--,o[i]=1;
			if(g&&c[i]==1&&merge(u[i],v[i])) g--,o[i]=1;
		}
	};
	shit(1);
	int d=n-1-k,tr=r,tg=g;
	lst=fa;lo=o;
	for(int i=0;i<=d;i++) if(i<=r&&d-i<=g){
		int nr=i,ng=d-i;
		fa=lst;o=lo;r=tr;g=tg;
		for(int i=0;i<m;i++){
			if(nr&&r&&!c[i]&&merge(u[i],v[i])) nr--,r--,o[i]=1;
			if(ng&&g&&c[i]==1&&merge(u[i],v[i])) ng--,g--,o[i]=1;
		}
		iota(begin(fa),end(fa),0);
		for(int i=0;i<m;i++) if(o[i]) merge(u[i],v[i]);
		shit(0);
		if(!r&&!g){
			for(int i=0;i<m;i++) if(c[i]==2&&merge(u[i],v[i])) o[i]=1;
			cout<<"YES\n";
			for(int i=0;i<m;i++) cout<<o[i];
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}