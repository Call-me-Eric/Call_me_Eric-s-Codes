#include<cstdio>
using namespace std;
int n,K,v,pri[99],cnt,ans[99],t[99],Ans;
void dfs(int nw,int rem){
	if(n+1-nw+K-rem<=Ans) return;
	if(nw>n){
		for(int i=1,x,y,p;i<=n;++i){
			x=y=0;p=i;
			for(int j=n/2;j--;) x+=t[p],p=p%n+1;
			for(int j=n/2;j--;) y+=t[p],p=p%n+1;
			if(x^y) return;
		}
		for(int i=1;i<=n;++i) ans[i]=t[i];
		Ans=n+1-nw+K-rem;
		return;
	}
	if(rem) t[nw]=1,dfs(nw+1,rem-1);
	t[nw]=0;dfs(nw+1,rem);
}
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&K);v=n;
	if(n==K){
		for(int i=1;i<=n;++i) putchar('1');
		return 0;
	}
	if(K<2){
		for(int i=1;i<=n;++i) putchar('0');
		return 0;
	}
	for(int i=2;i<=v;++i) if(v%i==0) for(pri[++cnt]=i;v%i==0;v/=i);
	if(cnt==1){
		for(int i=0;i<n;++i) putchar((i%(n/pri[1])<K/pri[1])?'1':'0');
		return 0;
	}
	dfs(1,K);
	for(int i=1;i<=n;++i) putchar(ans[i]?'1':'0');
	return 0;
}
