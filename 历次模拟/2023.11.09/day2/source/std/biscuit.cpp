#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n,m,c[1000010],a[1000010];
ll k,res=0;
int main(){
	freopen("biscuit.in","r",stdin);
	freopen("biscuit.out","w",stdout);

	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--){
		if(a[i]<=m) m-=a[i];
		else c[a[i]]++,c[m]--,m=0;
	}
	for(int i=1e6;i>=1;i--) c[i]+=c[i+1];
	for(int i=1e6;i>=1;i--){
		int mn=min(1ll*c[i],k);
		c[i]-=mn,k-=mn;
		res+=1ll*c[i]*i;
	}
	printf("%lld\n",res);
}
