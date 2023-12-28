#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum*fh;
}
#define maxn 200009
#define pb push_back
int n,m,d[maxn],cnt=0;
int f[maxn],siz[maxn],edge[maxn];
long long ans1=0;
int ans2=0;
int lf(int u){return u^f[u]?f[u]=lf(f[u]):u;}
void meg(int u,int v){
	u=lf(u),v=lf(v);
	if(u^v){
		f[v]=u;siz[u]+=siz[v];edge[u]+=edge[v];
	}
	edge[u]++;
	return ;
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1,edge[i]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		meg(u,v);
		d[u]++;d[v]++;
	}
	bool hasring=false;
	for(int i=1;i<=n;i++){
		if(d[i]>=3){
			int fi=lf(i);
			if(siz[fi]>4||edge[fi]>=siz[fi]){puts("-1");return 0;}
		}
		if(lf(i)==i){
			if(edge[i]==siz[i])hasring=true,ans2+=siz[i];
			else ans1+=1ll*siz[i]*(siz[i]+1)/2; 
		}
	}
	if(hasring){
		printf("%d %d\n",1,ans2);
	}
	else{
		printf("%d %lld\n",0,ans1);
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

