#include<bits/stdc++.h>
using namespace std;
int a[10001][10001];
int main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=n;i>1;i--){
		for(int j=1;j<i;j++){
			int maxn=0;
			maxn=max(a[i][j],a[i][j+1]);
			a[i-1][j]+=maxn;
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=i;j++){
//			printf("%d ",a[i][j]);
//		}
//		printf("\n");
//	}
	printf("%d",a[1][1]);
	return 0;
}
