#include<bits/stdc++.h>
using namespace std;
int dis[1000001],a[1000001];
int main(){
	freopen("iyue.in","r",stdin);
	freopen("iyue.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int q;
	scanf("%d",&q);
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=25;i++){
		dis[i*i]=1;
	}
	while(q--){
		int l,r;
		int ans=0;
		scanf("%d%d",&l,&r);
		for(int i=l;i<r;i++){
			for(int j=i+1;j<=r;j++){
				if(dis[a[i]+a[j]]==1){
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
