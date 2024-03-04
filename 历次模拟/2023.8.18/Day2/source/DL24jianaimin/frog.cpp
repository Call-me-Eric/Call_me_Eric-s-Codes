#include<bits/stdc++.h>
using namespace std;
int a[10000001],b[10000001],c[10000001],d[10000001],e[10000001],f[10000001];
int main(){
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d%d%d",&a[i],&b[i],&c[i],&e[i],&d[i],&f[i]);
		if(i!=1){
			int ans=0;
			for(int j=i-1;j>=1;j--){
				if(a[j]<=a[i]&&b[j]<=b[i]&&c[j]<=c[i]&&d[j]<=d[i]&&e[j]<=e[i]){
					ans=max(ans,f[j]);
				}
			}	
			f[i]+=ans;
		}
		
		printf("%d\n",f[i]);
	}
	return 0;
}
