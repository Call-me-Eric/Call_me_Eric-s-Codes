#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e6+7;
vector<int> vec[N];
int cnt[N];
int n;
int pos[N];

signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	mt19937 rnd(random_device{}()^time(0));
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&cnt[i]);
		for(int j=1;j<=cnt[i];j++){
			int t;scanf("%lld",&t);
			vec[i].push_back(t);
		}
		sort(vec[i].begin(),vec[i].end());
	}
	int jc=0x3f3f3f3f3f3f3f3f;
	for(int T=1;T<=100;T++){
		int maxx=-0x3f3f3f3f,minn=0x3f3f3f3f;
		for(int i=1;i<=n;i++){
			int mod=cnt[i]
			int rd=rnd()%mod;
			rd+=mod,rd%=mod;
			int val=vec[i][rd];
			maxx=max(maxx,val),minn=min(minn,val);
		}
		jc=min(jc,maxx-minn);
	}
	printf("%lld",jc);
	return 0;
}
