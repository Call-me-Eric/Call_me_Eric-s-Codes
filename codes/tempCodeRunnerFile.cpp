#include<bits/stdc++.h>
typedef long long LL;
 
using namespace std;
const int MAXN=3e5+10;
LL T,n;
LL a[MAXN],pw[30],sum[MAXN];
bool sf;
map<LL,pair<LL,LL> > mp;
void inpt(LL x,LL y) {
	if(sf) return ;
	LL ls=a[y]^a[x-1];
	if(!mp.count(ls)) {
		mp[ls].first=x;
		mp[ls].second=y;
		return ;
	} sf=1;
    printf("%lld,%lld %lld,%lld\n",x,y,mp[ls].first,mp[ls].second);
	if(mp[ls].second<x) printf("%lld %lld %lld %lld\n",mp[ls].first,mp[ls].second,x,y);
	if(mp[ls].first<x&&mp[ls].second>=x) printf("%lld %lld %lld %lld\n",mp[ls].first,x-1,mp[ls].second+1,y);
	if(mp[ls].first>x) printf("%lld %lld %lld %lld\n",x,mp[ls].first-1,mp[ls].second+1,y);
}
int main () {
	pw[0]=1;
	for(int i=1;i<=18;++i) pw[i]=pw[i-1]*2;
	scanf("%lld",&T);
	while(T--) {
		mp.clear();
		scanf("%lld",&n);
		for(int i=1;i<=pw[n+1];++i) {
			scanf("%lld",&a[i]);
			a[i]^=a[i-1];
		}
		for(int i=0;i<=pw[n];++i) sum[i]=-1;
		sum[0]=0; sf=0;
		for(int i=1;i<=pw[n+1];++i) {
			if(sum[(a[i]>>n)]!=-1) {
				inpt(sum[(a[i]>>n)]+1,i);
			}
			sum[(a[i]>>n)]=i;
		}
	}
	return 0;
}