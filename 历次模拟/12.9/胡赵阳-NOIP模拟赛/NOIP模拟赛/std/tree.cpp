#include<bits/stdc++.h>
using namespace std;
#define N 500005
struct Edge{
	int nex,to;
}edge[N<<1];
int E,n,x,y,num[11],a[N],head[N],g[N],f[N],ansg[N],ans[N];
int read(){
	int x=0;
	char c=getchar();
	while ((c<'0')||(c>'9'))c=getchar();
	while ((c>='0')&&(c<='9')){
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
void write(int x){
	while (x){
		num[++num[0]]=x%10;
		x/=10;
	}
	if (!num[0])putchar('0');
	while (num[0])putchar(num[num[0]--]+'0');
	putchar(' ');
}
void add(int x,int y){
	edge[E].nex=head[x];
	edge[E].to=y;
	head[x]=E++;
}
void dfs(int k,int fa){
	f[k]=g[k]=a[k];
	for(int i=head[k];i!=-1;i=edge[i].nex)
		if (edge[i].to!=fa){
			dfs(edge[i].to,k);
			int x=g[edge[i].to];
			if (f[k]<x)swap(f[k],x);
			g[k]=max(g[k],x);
		}
}
void calc(int k,int fa){
	ans[k]=f[k],ansg[k]=g[k];
	if (fa){
		int x=ansg[fa];
		if (ans[k]<x)swap(ans[k],x);
		ansg[k]=max(ansg[k],x);
	}
	for(int i=head[k];i!=-1;i=edge[i].nex)
		if (edge[i].to!=fa)calc(edge[i].to,k);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout); 
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++){
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	calc(1,0);
	for(int i=1;i<=n;i++)write(ans[i]);
	return 0;
}
