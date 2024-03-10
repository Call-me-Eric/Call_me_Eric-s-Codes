#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 110;
double a[maxn][maxn];
signed main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n + 1;j++){
			scanf("%lf",&a[i][j]);
		}
	}
	for(int i = 1;i <= n;i++){
		int Max = i;
		for(int j = i + 1;j <= n;j++){
			if(fabs(a[j][i]) > fabs(a[Max][i])){
				Max = j;
			}
		}
		for(int j = 1;j <= n + 1;j++){
			swap(a[i][j],a[Max][j]);
		}
		if(!a[i][i]){
			puts("No Solution");
			return 0;
		}
		for(int j = 1;j <= n;j++){
			if(j != i){
				double tmp = a[j][i] / a[i][i];
				for(int k = i + 1;k <= n + 1;k++){
					a[j][k] -= (a[i][k] * tmp);
				}
			}
		}
	}
	for(int i = 1;i <= n;i++){
		printf("%.2lf\n",a[i][n + 1] / a[i][i]);
	}
	return 0;
}

