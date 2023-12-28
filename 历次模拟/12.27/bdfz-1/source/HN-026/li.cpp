#include <cstdio>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=200003;
int n,m;
int deg[N];
bool vis[N];
int hd[N],ver[N<<1],nxt[N<<1],tot;
void add(int u,int v){
	nxt[++tot]=hd[u];hd[u]=tot;ver[tot]=v;
}
int cnt;
void dfs(int u,int fa){
	vis[u]=1;++cnt;
	for(int i=hd[u];i;i=nxt[i]){
		int v=ver[i];
		if(v==fa||vis[v]) continue;
		dfs(v,u);
	}
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		add(u,v);add(v,u);
		++deg[u];++deg[v];
	}
	for(int i=1;i<=n;++i)
		if(deg[i]>3){
			puts("-1");
			return 0;
		}
	int sum=0;
	for(int u=1;u<=n;++u)
		if(deg[u]==3){
			for(int i=hd[u];i;i=nxt[i]){
				int v=ver[i];
				if(deg[v]>1){
					puts("-1");
					return 0;
				}
				vis[v]=1;
			}
			vis[u]=1;
			sum+=3;
		}
	long long tmp=0;
	for(int i=1;i<=n;++i)
		if(!vis[i]&&deg[i]<=1){
			dfs(i,0);
			tmp+=(long long)cnt*(cnt+1)>>1;
			cnt=0;
		}
	for(int i=1;i<=n;++i)
		if(!vis[i]){dfs(i,0);sum+=cnt;cnt=0;}
	if(sum) printf("1 %d\n",sum);
	else printf("0 %lld\n",tmp);
	return 0;
}
