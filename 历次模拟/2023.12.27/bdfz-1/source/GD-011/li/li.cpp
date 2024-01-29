#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,m,lst[N],tot,i,x,y,r[N],cntl,cnth,cnt;
long long sum;
bool vis[N];
struct node{
	int y,n;
}d[N<<1];
void cun(int x,int y){
	d[++tot]=node{y,lst[x]};
	lst[x]=tot;
}
void dfs(int x){
	vis[x]=1;
	cntl++,cnt++;
	for(int j=lst[x];j;j=d[j].n)
		if(!vis[d[j].y])dfs(d[j].y);
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		cun(x,y),cun(y,x);
		r[x]++,r[y]++;
	}
	for(i=1;i<=n;i++)
	if(r[i]>=4) return puts("-1"),0;
	else if(r[i]==3){
		vis[i]=1;
		for(int j=lst[i];j;j=d[j].n)
			if(r[d[j].y]>1) return puts("-1"),0;
			else vis[d[j].y]=1;
	}
	for(i=1;i<=n;i++)
	if(r[i]<=1&&!vis[i]) cnt=0,dfs(i),sum+=1ll*cnt*(cnt+1)/2;
	if(cntl==n) return printf("0 %lld",sum),0;
	else printf("1 %d",n-cntl);
	return 0;
}
