#include<bits/stdc++.h>
using namespace std;
int fa[200005],ff[200005],ee[200005],deg[200005];
int vv[200005],v2[200005];
int findfather(int x){
	return x==fa[x]?x:fa[x]=findfather(fa[x]);
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)fa[i]=i,ff[i]=1,ee[i]=deg[i]=vv[i]=v2[i]=0;
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		++deg[u],++deg[v];
		int fu=findfather(u),fv=findfather(v);
		++ee[fu];
		if(fu!=fv)fa[fu]=fv,ff[fv]+=ff[fu],ee[fv]+=ee[fu];
	}
	for(int i=1;i<=n;++i){
		if(deg[i]>2)++vv[findfather(i)];
		if(deg[i]>3)++v2[findfather(i)];
	}
	int gs=0;long long sg=0;
	for(int i=1;i<=n;++i)if(fa[i]==i){
		if(ee[i]>ff[i]){
			puts("-1");
			return 0;
		}
		if(ee[i]==ff[i]){
			if(vv[i]){
				puts("-1");
				return 0;
			}
			gs+=ff[i];
		}else{
			if(v2[i]){
				puts("-1");
				return 0;
			}
			if(vv[i]&&ff[i]>4){
				puts("-1");
				return 0;
			}
			if(vv[i]&&ff[i]==4)gs+=ff[i]-1;
			else sg+=1ll*ff[i]*(ff[i]+1)/2;
		}
	}
	if(gs)printf("1 %d\n",gs);
	else printf("0 %lld\n",sg);
	return 0;
}
