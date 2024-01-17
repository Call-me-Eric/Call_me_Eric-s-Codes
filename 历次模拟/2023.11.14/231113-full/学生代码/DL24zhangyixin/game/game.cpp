#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
int n,l,r,a[N];
int sum,num;
signed main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%lld %lld %lld",&n,&l,&r);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	sum=0;num=0;
	for(int i=1;i<=n;i+=2) sum+=a[i];
	for(int i=n;i>=1;i-=2) num+=a[i];
	if(sum<l||num>r) printf("Alice");
	else printf("Bob");
	return 0;
}
