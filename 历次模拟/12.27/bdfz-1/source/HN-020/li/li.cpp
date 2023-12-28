//Code by juju527.
#include<bits/stdc++.h>
typedef long long ll;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector<int>
#define eb emplace_back
using namespace std;
const int maxn=2e5+5;
int d[maxn];
vec e[maxn];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
vec p;
bool vis[maxn];
void dfs(int x){
	p.eb(x),vis[x]=1;
	for(auto y:e[x])if(!vis[y])dfs(y);
	return ;
}
int cnt[5];
ll S1(int x){return 1ll*x*(x+1)/2;}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int n,m;
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read(),v=read();
		e[u].eb(v),e[v].eb(u);
		d[u]++,d[v]++;
	}
	int mx=0;
	for(int i=1;i<=n;i++)mx=max(mx,d[i]);
	if(mx>=4){puts("-1");return 0;}
	int s=0;ll ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		p.clear();dfs(i);
		if(p.size()==1){
			if(!s)ans++;
			continue;
		}
		cnt[1]=cnt[2]=cnt[3]=0;
		for(auto x:p)cnt[d[x]]++;
		if(!cnt[1]&&!cnt[3]){
			if(!s)ans=0,s=1;
			ans+=p.size();
		}
		else if(!cnt[3]&&cnt[1]==2){
			if(!s)ans+=S1(p.size());
		}
		else if(cnt[3]==1&&cnt[1]==3&&!cnt[2]){
			if(!s)ans=0,s=1;
			ans+=3;
		}
		else{
			puts("-1");
			return 0;
		}
	}
	printf("%d %lld\n",s,ans);
	return 0;
}
