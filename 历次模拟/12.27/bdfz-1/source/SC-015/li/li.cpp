#include<cstdio>
using namespace std;
const int o=4e5+10;
int n,m,h[o],cnt,d[o],s,st[o],tp;long long ans;bool vis[o];
struct Edge{int v,p;}e[o];
inline void ad(int U,int V){e[++cnt].v=V;e[cnt].p=h[U];h[U]=cnt;}
void dfs(int nw){
	vis[st[++tp]=nw]=1;
	for(int i=h[nw];i;i=e[i].p){
		++m;
		if(!vis[e[i].v]) dfs(e[i].v);
	}
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int u,v;m--;) scanf("%d%d",&u,&v),ad(u,v),ad(v,u),++d[u],++d[v];
	for(int i=1;i<=n;++i) if(d[i]>=4){printf("-1");return 0;}
	for(int i=1,flg;i<=n;++i) if(!vis[i]){
		tp=m=flg=0;dfs(i);m/=2;
		for(int j=1;j<=tp;++j) if(d[st[j]]==3) flg=1;
		if(flg){
			if(m>3){printf("-1");return 0;}
			if(!s) s=1,ans=0;
			ans+=3;
		}
		else if(m==tp){
			if(!s) s=1,ans=0;
			ans+=m;
		}
		else if(!s) ans+=tp*(tp+1ll)/2;
	}
	printf("%d %lld",s,ans);
	return 0;
}
