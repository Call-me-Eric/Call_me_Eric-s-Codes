#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1.0);
#define N 1<<20|5
int n,k,i,ans,u;
struct node{
	double ss,sc;
}d[N],e[N];
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(k==n||!k||k==1||n>36){
		for(i=1;i<=n;i++) printf("%d",k/n);return 0;
	}
	for(i=1;i<(1<<n);i++){
		int t=-i&i;
		d[i].ss=d[i^t].ss+sin(2*pi*__lg(t)/n);
		d[i].sc=d[i^t].sc+cos(2*pi*__lg(t)/n);
		if(fabs(d[i].ss)<1e-9&&fabs(d[i].sc)<1e-9&&__builtin_popcount(i)<=k&&__builtin_popcount(i)>__builtin_popcount(ans)) ans=i; 
	}
	for(int i=0;i<n;i++) printf("%d",ans>>i&1);
	return 0;
}
