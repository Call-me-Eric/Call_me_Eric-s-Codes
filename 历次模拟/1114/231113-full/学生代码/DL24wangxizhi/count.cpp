#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10,mod=998244353;
int n,ans,res;
vector<int>e[maxn];
int a[maxn],b[maxn],col[maxn];
inline void add(int x,int y){e[x].push_back(y),e[y].push_back(x);} 
inline int qpow(int s,int t)
{
	int res=1,base=s%mod;
	while(t){if(t&1)res=res*base%mod;base=base*base%mod;t>>=1;}
	return res;
}
struct DSU
{
	DSU(){iota(fad,fad+maxn,0);}
	int fad[maxn],cir[maxn];
	inline int find(int x){return fad[x]==x?x:fad[x]=find(fad[x]);}
	inline void merge(int x,int y)
	{
		x=find(x),y=find(y);
		if(cir[x] && cir[y]) return res=0,void();
		if(x==y) return cir[x]=1,void();
		col[x]|=col[y],cir[x]|=cir[y],fad[y]=x;
	}
}dsu;
inline void fill(int x)
{
	for(auto y:e[x])
		if(col[y]==col[x]){ cout<<ans<<endl;exit(0);}
		else if(!col[y]) col[y]=col[x]%2+1,fill(y);
}
inline void solve()
{
	cin>>n,res=1,ans=qpow(n,n);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) if(a[i]==b[i])
		res=res*n%mod,col[a[i]]=1;
	for(int i=1;i<=n;i++) if(a[i]!=b[i]) 
		add(a[i],b[i]),dsu.merge(a[i],b[i]);
	
	
	vector<int>vec;
	if(!res) return cout<<ans<<'\n',void(); 
	for(int i=1;i<=n;i++) if(col[i]) vec.push_back(i);
	for(auto x:vec) fill(x); 
	
	for(int i=1;i<=n;i++) if(dsu.fad[i]==i && !col[i]) res=res*2%mod;
	cout<<(ans-res+mod)%mod<<endl;
}
signed main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
