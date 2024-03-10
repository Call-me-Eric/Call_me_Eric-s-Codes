#include<bits/stdc++.h>
#define read(a) scanf("%d",&a)
using namespace std;
const int N=5e4+5;
int n,a,b,c,d,e;
int dp[N],vis[N];
struct stone{
	int h,l,v;
}s[N];
void dfs(int x){
	for(int i=1;i<=n;i++){
		if(x==i)  continue;
		if(s[x].h<=s[i].l){
			dp[i]=max(dp[i],dp[x]+s[i].v);
			vis[i]=1;
			dfs(i);
		}
	}
}
int main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++){
		read(a);read(b);read(c);read(d);read(e);read(s[i].v);
		s[i].h=max(max(a,b),max(c,max(d,e)));
		s[i].l=min(min(a,b),min(c,min(d,e)));
		dp[i]=s[i].v;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",dp[i]);
	}
	return 0;
}
