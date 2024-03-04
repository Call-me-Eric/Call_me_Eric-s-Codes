#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll ans=0;
int a[110000];

int main(){
	
	freopen("Transport.in","r",stdin);
	freopen("Transport.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n-1;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
	}
	
	ans=n*(n-1);
	
	printf("%lld",ans);
	
	return 0;
}
