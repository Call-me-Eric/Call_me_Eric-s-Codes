#include<bits/stdc++.h>
using namespace std;
int a[5][100001];
int main(){
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		int flag=0;
		for(int i=1;i<=4;i++){
			for(int j=1;j<=3;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=0;i<=10;i++){
			for(int j=0;j<=10;j++){
				for(int k=0;k<=10;k++){
					if(i*a[1][1]+j*a[2][1]+k*a[3][1]==a[4][1]&&i*a[1][2]+j*a[2][2]+k*a[3][2]==a[4][2]&&i*a[1][3]+j*a[2][3]+k*a[3][3]==a[4][3]){
						printf("YES");
						printf("\n");
						flag=1;
						break;
					}
				}
				if(flag==1){
					break;
				}
			}
			if(flag==1){
				break;
			}
		}
		if(flag==0){
			printf("NO");
			printf("\n");
		}
	}
	
	return 0;
}
