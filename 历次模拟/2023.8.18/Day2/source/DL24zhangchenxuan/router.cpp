#include<bits/stdc++.h>
#define int long long
#define read(a) scanf("%lld",&a)
using namespace std;
const int N=1e6+5;
int n,ans,v,u,low,k;
int a[N],vis[N];
vector<int>b[N];
signed main(){
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=1;i<n;i++){
		read(u);read(v);
		b[u].push_back(v);
		b[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		low=a[i];
		k=i;
		for(auto j:b[i]){
			if(low>=a[j]){
				low=a[j];
				k=j;
			}
		}
		if(vis[k])  continue;
		vis[k]=1;
		ans+=a[k];
	}
	printf("%lld",ans);
}
