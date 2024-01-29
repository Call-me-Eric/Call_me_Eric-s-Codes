#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
mt19937 rnd(time(0));
template <typename tp> struct Fenwick {
	vector<tp>c;
	Fenwick(int n) {c.resize(n+1);}
	inline int lowbit(int x) {return x&(-x);}
	inline void add(int x,tp d) {
		for(;x<(int)c.size();x+=lowbit(x))c[x]+=d;
	}
	inline tp query(int x) {
		tp res=0;
		for(;x>=1;x-=lowbit(x))res+=c[x];
		return res;
	}
	inline tp rangequery(int l,int r) {
		return query(r)-query(l-1);
	}
};
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int>a(n+1);
	vector<int>disc;
	for(ri i=1;i<=n;i++)scanf("%d",&a[i]),disc.push_back(a[i]);
	vector<int>l(m+1),r(m+1),k(m+1);
	for(ri i=1;i<=m;i++) {
		int op;
		scanf("%d%d%d",&op,&l[i],&r[i]);
		if(op==2)scanf("%d",&k[i]);
		else disc.push_back(r[i]);
	}
	sort(disc.begin(),disc.end());
	disc.resize(unique(disc.begin(),disc.end())-disc.begin());
	for(ri i=1;i<=n;i++)a[i]=lower_bound(disc.begin(),disc.end(),a[i])-disc.begin()+1;
	for(ri i=1;i<=m;i++)
		if(!k[i])r[i]=lower_bound(disc.begin(),disc.end(),r[i])-disc.begin()+1;
	vector<int>ans(m+1,1);
	int mx=(int)disc.size();
	for(ri t=0;t<30;t++) {
		vector<int>f(mx+1);
		for(ri i=1;i<=mx;i++)f[i]=rnd()%998244353;
		Fenwick<ll>fen(n+1);
		auto b=a;
		for(ri i=1;i<=n;i++)b[i]=f[b[i]],fen.add(i,b[i]);
		for(ri i=1;i<=m;i++) {
			if(!k[i]) {
				fen.add(l[i],f[r[i]]-b[l[i]]);
				b[l[i]]=f[r[i]];
			}
			else {
				ans[i]&=fen.rangequery(l[i],r[i])%k[i]==0;
			}
		}
	}
	for(ri i=1;i<=m;i++)
		if(k[i])printf("%s\n",ans[i]?"YES":"NO");
	return 0;
}

