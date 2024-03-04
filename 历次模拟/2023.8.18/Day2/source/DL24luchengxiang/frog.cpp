#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
const int N=5e4+5;
int n,a[N][6],f,ans[N],res;
signed main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++)scanf("%d",&a[i][j]);scanf("%d",&f);
		bool p;int res=0;
		for(int j=i-1;j;j--){p=1;for(int k=1;k<=5;k++)p&=(a[i][k]>=a[j][k]);if(p)res=max(res,ans[j]);}
		ans[i]=res+f;
		printf("%d\n",ans[i]);
	}
	return 0;
}

