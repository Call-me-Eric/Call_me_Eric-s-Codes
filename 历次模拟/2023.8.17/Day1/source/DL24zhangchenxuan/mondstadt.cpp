#include<bits/stdc++.h>
#define read(a) scanf("%lld",&a)
#define int long long
using namespace std;
const int N=1e6+5,M=2e6+5,mod=1e9+7;
int n,m,u,v,ans;
int cnt[N];
vector<int>a[N];
int zs(int x,int y){
	int fm=y,fz=1;
	for(int i=2;i<=x;i++){
		fz*=i;
		fz%=mod;
	}
	for(int i=y-1;i>y-x;i--){
		fm*=i;
		fm%=mod;
	}
	return fm/fz%mod;
}
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=m;i++){
		read(u);read(v);
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		int b=0;
		for(auto j:a[i]){
			b++;
		}
		for(int k=2;k<=b;k++){
			cnt[k]+=zs(k,b);
		}
	}
	ans=cnt[2];
	for(int i=3;i<n;i++){
		ans^=cnt[i];
	}
	printf("%lld",ans);
}
