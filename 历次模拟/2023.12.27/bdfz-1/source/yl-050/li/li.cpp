#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
const int inf=1e9;
#define ll long long
#define pb push_back
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[maxn],d[maxn],k,f[maxn],sz[maxn],tg[maxn];
vector<int>G[maxn];ll ans;
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)tg[x]=1;
	else f[x]=y,sz[y]+=sz[x],tg[y]|=tg[x];
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)f[i]=i,sz[i]=1,tg[i]=0;
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		++d[x],++d[y],G[x].pb(y),G[y].pb(x);
		merge(x,y);
	}
	for(int i=1;i<=n;i++)
		if(d[i]>=4)return puts("-1"),0;
	for(int i=1;i<=n;i++)if(d[i]==3){
		k=1;int flg=1;
		for(auto x:G[i])flg&=(d[x]==1);
		if(!flg)return puts("-1"),0;
		ans+=3;
	}
	for(int i=1;i<=n;i++)
		if(find(i)==i&&tg[i])k=1,ans+=sz[i];
	if(k)return printf("1 %lld\n",ans),0;
	for(int i=1;i<=n;i++)
		if(find(i)==i)ans+=1ll*sz[i]*(sz[i]+1)/2;
	printf("0 %lld\n",ans);
	return 0;
}
