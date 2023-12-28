#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=2e5+10;
int n,m,fl,ans;
int fa[N],used[N],sz[N];
vector<int> g[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void S_Not_Exist(){puts("-1"),exit(0);}
int sum(int l,int r){return (l+r)*(r-l+1)/2;}
int deg[N];
signed main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read(),m=read();
	For(i,1,n)fa[i]=i,sz[i]=1;
	For(i,1,m){
		int u=read(),v=read();
		deg[u]++,deg[v]++;
		g[u].push_back(v);
		g[v].push_back(u);
		u=get(u),v=get(v);
		if(u==v){
			if(!used[u])used[u]=1,fl=1;
			else S_Not_Exist();
		}else{
			fa[u]=v,sz[v]+=sz[u];
			if(used[u]&&used[v])S_Not_Exist();
			used[v]|=used[u];
		}
	}
	For(u,1,n)if(deg[u]>=4)S_Not_Exist();
	For(u,1,n)if(deg[u]==3){for(int v:g[u])if(deg[v]>1)S_Not_Exist();fl=1,ans+=3;}
	if(!fl){
		For(i,1,n)if(get(i)==i)ans+=sum(1,sz[i]);
		printf("0 %lld\n",ans);
	}else{
		For(i,1,n)if(get(i)==i&&used[i])ans+=sz[i];
		printf("1 %lld\n",ans);
	}
	return 0;
}
