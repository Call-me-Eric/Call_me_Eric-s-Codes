#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=2e6+10;
int n,c[N],p[N],cnt,S,T,lim;
int pos[N],rec,Mx[N],Mn[N];
vector<pii> vec[N];
vector<int> g[N];
inline bool cmp(int x,int y){
	return c[x]<c[y];
}
int ans=2e10;
bool dfs(int x,int mx,int mn){
	//cerr<<x<<endl;
	if(x!=S&&mx-mn>lim)return 0;
	if(x!=S&&Mx[x]<=mx&&Mn[x]>=mn)return 0;
	if(x!=S&&(mx<=Mx[x]&&mn>=Mn[x])){
		Mx[x]=mx;Mn[x]=mn;
	}
	if(x==T){
		return 1;
	}
	for(int i:g[x]){
		int nmx=mx,nmn=mn;
		if(i!=T){
			nmx=max(nmx,pos[i]);
			nmn=min(nmn,pos[i]);
		}
		if(dfs(i,nmx,nmn))return 1;
	}
	return 0;
}
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;i++){
		c[i]=rd();
		for(int j=1;j<=c[i];j++){
			int x=rd();
			vec[i].emplace_back(x,++cnt);
			pos[cnt]=x;
			//Mx[cnt]=-1e9;Mn[cnt]=1e9;
		}
		sort(vec[i].begin(),vec[i].end());
	}
	//cout<<rec<<endl;
	for(int i=1;i<=n;i++){
		p[i]=i;
	}
	sort(p+1,p+1+n,cmp);
	S=++cnt;T=++cnt;
	for(pii i:vec[p[1]]){
		g[S].push_back(i.sc);
	}
	for(pii i:vec[p[n]]){
		g[i.sc].push_back(T);
	}
	for(int i=1;i<n;i++){
		int u=p[i],v=p[i+1];
		for(int j=0;j<vec[u].size();j++){
			auto res=lower_bound(vec[v].begin(),vec[v].end(),(pii){vec[u][j].fr,0});
			if(res!=vec[v].end()){
				g[vec[u][j].sc].push_back((*res).sc);
			}
			if(res!=vec[v].begin()){
				res--;
				g[vec[u][j].sc].push_back((*res).sc);
			}
		}
	}
	int l=-1,r=2e9+1;
	while(l!=r-1){
		lim=(l+r)/2;
		for(int i=1;i<=cnt;i++){
			Mx[i]=1e9;Mn[i]=-1e9;
		}
		//cerr<<lim<<endl;
		if(dfs(S,-1e9,1e9))r=lim;
		else l=lim;
	}
	cout<<r<<endl;
	return 0;
}

