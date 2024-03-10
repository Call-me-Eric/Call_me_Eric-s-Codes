#include<bits/stdc++.h>
using namespace std;
int a[1001][1001],vis1[100001];
int mian(){	
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int ans=n*m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	int minn=min(n,m);
	for(int k=1;k<minn;k++){
		for(int i=1;i<=n-minn;i++){
			for(int j=1;j<=m-minn;j++){
				memset(vis1,0,sizeof(vis1));
				int cnt=0;
				for(int w=0;w<=k;w++){
					int an=a[i-w][j-w];
					int flag=0;
					for(int v=1;v<=k-w+1;v++){
						if(a[i-w][j-w]!=an){
							flag=1;
							break;
						}
					}
					if(flag){
						cnt=1;
						break;
					}else{
						if(vis1[an]==1){
							cnt=1;
							break;
						}else{
							vis1[an]==1;
						}
					}
				}
				if(cnt==0){
					ans++;
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
