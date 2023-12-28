#include<bits/stdc++.h>
using namespace std;
int r,g,b,n,m,u[1000001],v[1000001],cas[1000001],vis[1000001],e[1000001],cnt[101];char s[10];
void dfs(int x){
	vis[x]=1;
	for(int i=0;i<m;i++){
		if(e[i]){
			if(u[i]==x)if(!vis[v[i]])dfs(v[i]);
			if(v[i]==x)if(!vis[u[i]])dfs(u[i]);
		}
	}
}
int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin>>r>>g>>b>>m;n=r+g+b+1;
	for(int i=0;i<m;i++){
		scanf("%d%d%s",&u[i],&v[i],s+1);
		if(s[1]=='r')cas[i]=1;
		if(s[1]=='g')cas[i]=2;
		if(s[1]=='b')cas[i]=3;
	}
	for(int i=1;i<(1<<m);i++){
		if(__builtin_popcount(i)!=n-1)continue;
		for(int j=0;j<m;j++)if((1<<j)&i)e[j]=1,cnt[cas[j]]++;else e[j]=0;
		if(cnt[1]!=r||cnt[2]!=g)continue;
		dfs(1);int f=1;for(int j=1;j<=n;j++)if(!vis[j])f=0;
		if(f){
			puts("YES");
			for(int j=0;j<m;j++)cout<<((i>>j)&1);
			return 0;
		}
		cnt[1]=cnt[2]=cnt[3]=0;
		for(int j=1;j<=n;j++)vis[j]=0;
	}puts("NO");
}
