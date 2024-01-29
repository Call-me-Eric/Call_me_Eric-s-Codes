#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
int Qpow(int a,int b){int ret=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ret=1ll*ret*a%mod;return ret;}
int n,q;
int a[705][705];
int b[705][705];
void query(){
	memcpy(b,a,sizeof b);
	for(int i=1;i<=n;++i){
		int now=-1;
		for(int j=i;j<=n;++j){
			if(b[i][j]!=0){
				now=j;
				break;
			}
		}
		if(now==-1)continue;
		for(int j=1;j<=n+1;++j)
			swap(b[i][j],b[now][j]);
		for(int j=1;j<=n;++j){
			if(j==i || b[j][i]==0)continue;
			int K=1ll*Qpow(b[j][i],mod-2)*b[i][i]%mod;
			for(int k=1;k<=n+1;++k)
				b[j][k]=(1ll*K*b[j][k]%mod-b[i][k]+mod)%mod;
		}
	}
	int fl=0;
	for(int i=1;i<=n;++i){
		if(b[i][i]==0)
			fl=max(fl,1);
		if(b[i][i]==0 && b[i][n+1]!=0)
			fl=max(fl,2);
	}
	if(fl==1)
		printf("Many\n");
	else if(fl==2)
		printf("No\n");
	else{
		for(int i=1;i<=n;++i)
			printf("%lld%c",1ll*Qpow(b[i][i],mod-2)*b[i][n+1]%mod," \n"[i==n]);
	}
}

int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n+1;++j)
			scanf("%d",&a[i][j]);
	}
	query();
	while(q--){
		int z;
		scanf("%d",&z);
		for(int j=1;j<=n+1;++j)
			scanf("%d",&a[z][j]);
		query();
	}
}
