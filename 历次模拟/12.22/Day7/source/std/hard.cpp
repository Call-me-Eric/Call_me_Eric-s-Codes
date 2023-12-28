#include<bits/stdc++.h>
#define LL long long
#define N 100005
using namespace std;
const int mo=1e9+7;
LL f[N]; int m,n,cnt[N]; char str[N];
LL fpm(LL x,LL y){ LL s=1; while(y){ if(y&1) s=(s*x)%mo; y>>=1,x=(x*x)%mo;} return s;}
int main()
{
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
	int i,ans=0;
	scanf("%d",&m),n=0;
	for(i=1;i<=m;i++)
		scanf("%d",&cnt[i]),n+=cnt[i];
	f[1]=1LL*(n-1)*(n-1)%mo*fpm(n,mo-2)%mo;
	for(i=1;i<N-1;i++)
		f[i+1]=((2*f[i]-f[i-1]-(n-1)*fpm(n-i,mo-2)%mo)%mo+mo)%mo;
	for(i=1;i<=m;i++)
		(ans+=f[cnt[i]])%=mo;
	cout<<ans;
	return 0;
}
