#include<bits/stdc++.h>
using namespace std;
#define N 16
#define mod 1000000007
#define ll long long
vector<int>v;
int n,m,a[N],g[1<<N],h[1<<N],dp[1<<N];
int lowbit(int k){
	return (k&(-k));
}
int main(){
	freopen("partition.in","r",stdin);
	freopen("partition.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int S=0;S<(1<<n);S++){
		for(int i=0;i<n;i++)
			if ((S>>i)&1)g[S]^=a[i];
		g[S]++;
	}
	for(int S=1;S<(1<<n);S++){
		h[S]=g[S];
		int x=(S^lowbit(S));
		for(int i=x;i;i=((i-1)&x))h[S]=(h[S]-(ll)g[i]*h[S^i]%mod+mod)%mod;
	}
	dp[0]=1;
	for(int S=1;S<(1<<n);S++){
		int x=(S^lowbit(S));
		for(int i=x;;i=((i-1)&x)){
			dp[S]=(dp[S]+(ll)m*h[S^i]%mod*dp[i])%mod;
			if (!i)break;
		}
	}
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}
