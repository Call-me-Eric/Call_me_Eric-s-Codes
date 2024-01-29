#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define gc getchar
#define pc putchar
#define cs const

inline int getint(){
	re int num;
	re char c;
	while(!isdigit(c=gc()));num=c^48;
	while(isdigit(c=gc()))num=(num<<1)+(num<<3)+(c^48);
	return num;
}

cs int N=105;
int n;
bool g[N][N],to[N];
int match[N],idx;
int vis[N];
bool ban[N],s[N],t[N];

inline bool find(int u){
	if(ban[u])return false;
	for(int re v=1;v<=n;++v){
		if((vis[v]^idx)&&g[u][v]&&!ban[v]){
			vis[v]=idx;
			if(!match[v]||find(match[v])){
				to[u]=true,match[v]=u;
				return true;
			}
		}
	}
	return false;
}

inline void dfs(int u){
	if(s[u])return ;
	s[u]=true;
	for(int re v=1;v<=n;++v){
		if(g[u][v]&&!t[v])t[v]=true,dfs(match[v]);
	}
}

int m;
signed main(){
	n=getint(),m=getint();
	for(int re i=1;i<=m;++i){
		int u=getint(),v=getint();
		g[u][v]=1;
	}
	
	for(int re k=1;k<=n;++k)
	for(int re i=1;i<=n;++i)
	for(int re j=1;j<=n;++j)
	g[i][j]=g[i][j]||(g[i][k]&&g[k][j]);
	
	int ans=n;
	for(int re i=1;i<=n;++i){
		++idx;
		if(find(i))--ans;
	}
	printf("%d\n",ans);
	
	for(int re i=1;i<=n;++i)if(!to[i])dfs(i);
	for(int re i=1;i<=n;++i)printf("%d",s[i]&&!t[i]);
	pc('\n');
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			printf("%d",g[i][j]);
		}
		puts("");
	}
	for(int re k=1;k<=n;++k){
		memset(match,0,sizeof match);
		memset(to,0,sizeof to);
		memset(ban,0,sizeof ban);
		int tmp=0;
		
		for(int re i=1;i<=n;++i)
		if(g[i][k]||g[k][i]||i==k)ban[i]=true;
		else ++tmp;
		// printf("cnt = %d",tmp);
		for(int re i=1;i<=n;++i){
			++idx;
			if(find(i))--tmp;
		}
		// printf(",tmp = %d\n",tmp);
		printf("%d",tmp==ans-1);
		
	}
	return 0;
}
