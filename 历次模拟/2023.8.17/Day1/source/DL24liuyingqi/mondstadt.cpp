#include<bits/stdc++.h>
using namespace std;
#define int long long
//啥也我去 写破防了 能过啥呀我去。 
int n,m;
const int mod=1e9+7;
const int N=2e6+7;
vector<int> G[N];
int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}
struct node{
  int inv[2000090],fac[2000090];
  int qpow(int shu,int cifang){
    int ans=1;int k=cifang;
    while(k){
      if(k&1){ans=ans*shu%mod;ans%=mod;shu=shu*shu%mod;shu%=mod;}
      else{shu=shu*shu%mod;shu%=mod;}
      k>>=1;
    }
    return ans%mod;
  }
  void init(int len){
    fac[0]=1;
    for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%mod;
    inv[len]=qpow(fac[len],mod-2);
    for(int i=len;i;i--){
      inv[i-1]=inv[i]*(i)%mod;
    }
  }
  int C(int n,int m){
    return fac[n]%mod*inv[m]%mod*inv[n-m]%mod;
  }
}lg_get;

int maxx=0;

void solve(){
	int n=read(),m=read();
//	scanf("%lld%lld",&n,&m);
//	if(m==n-1&&n>5000){
//		
//	}
//	int tmp=0;
//	for(int i=1;i<=n-1;i++){
//		tmp=tmp^i;
//	}
//	printf("%lld\n",tmp);
	for(int i=1;i<=m;i++){
//		int u,v;scanf("%lld%lld",&u,&v);
		int u=read(),v=read();
		G[u].push_back(v);G[v].push_back(u);
	}
//	printf("Done"); 
//	return;
	for(int i=1;i<=n;i++) maxx=max(maxx,(long long)G[i].size());
	lg_get.init(maxx*2+3);
//	for(int i=1;i<=n;i++) printf("%d ",G[i].size());
	int sum=0;
//	printf("%lld\n",maxx);
	int ans=0;
//	int sum=0;
	for(int i=2;i<=maxx;i++){
		int res=0;
//		printf("i:%lld\n",i);
		for(int j=1;j<=n;j++){
			if(G[j].size()<i) continue;
//			sum++;
//			printf("j:%lld\n",j);
			res+=lg_get.C(G[j].size(),i);
			res%=mod;
		}
//		printf("res:%lld\n",res);
		ans^=res;
	}
//	printf("%lld",sum);
	printf("%lld",ans);
}

signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
  solve();
  return 0;
}
