#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return rng()%(r-l+1)+l;
}
int n,m,a[100010];
ll k,sum=0;
void split(int l,int r,int sum){
	assert(sum>=(r-l+1)&&sum<=(r-l+1ll)*m);
	if(l==r) return a[l]=sum,void();
	int mid=(l+r)>>1,lsum=ran(max(mid-l+1ll,sum-ll(r-mid)*m),min((mid-l+1ll)*m,sum-ll(r-mid)));
	split(l,mid,lsum),split(mid+1,r,sum-lsum);
}
int main(){
	n=ran(1000,2000),m=ran(50000,1e6);
	sum=ran(n,1e6);
	split(1,n,sum);
	printf("%d %d %lld\n",n,m,k=ran(sum/100,sum));
	for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
}

