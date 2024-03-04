#include <iostream>
#include <cstdio>
#define maxn 1000000
using namespace std;
int n,k,a[300005];
int mn[1000005],mx[1000005];
int ans;
int main(){
	freopen("gcd.in","r",stdin);
	freopen("gcd.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=1;i<=maxn;i++)mn[i]=n+1,mx[i]=0;
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mn[a[i]]=min(mn[a[i]],i);
		mx[a[i]]=max(mx[a[i]],i);
	}
	for (int i=1;i<=maxn;i++){
		int l=n+1,r=0;
		for (int j=i;j<=maxn;j+=i){
			l=min(l,mn[j]);
			r=max(r,mx[j]);
		}
		if (r-l>=k)ans=i;
	}
	printf("%d\n",ans);
	return 0;
}