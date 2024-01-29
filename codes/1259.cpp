#include <cstdio>
#include <iostream>
using namespace std;
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int len[201], to[201];
int a[201];
int n;
int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		to[i] = i;//初始最长的就是他自己 
		len[i] = 1;
	}
	for(int i = n;i >= 1;i--){
		int l = 0, k = i;
		for(int j = i + 1;j <= n;j++){
			if(a[i] <= a[j] /*符合要求*/
			&& len[j] > l/*还得最长*/){
				l = len[j];
				k = j;
			}
			if(l != 0){//have found
				len[i] = l + 1;
				to[i] = k;
			}
		}
	}
	int _max = -999, first = 0;
	for(int i = 1;i <= n;i++){
		if(len[i] > _max){
			_max = len[i];
			first = i;
		}
	}
	printf("max=%d\n",_max);
	int i = first;
	while(1){
		printf("%d ",a[i]);
		if(i == to[i])break;
		i = to[i];
	}
	return 0;
}

