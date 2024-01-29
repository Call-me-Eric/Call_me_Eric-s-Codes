#include <iostream>
#include <cstdio>
using namespace std;
const int n = 5, inf = 9999999;
int a[n + 1][n + 1], book[n + 1][n + 1];
int main() {
	int i, j, u, v, min = inf, temp = inf;
	int minx = 1, miny = 1;
	for(i = 1;i <= n;i++){
		for(j = 1;j <= n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	min = a[1][1];
	for(i = 1;i <= n;i++){
		for(v = 1;v <= n;v++)
		temp = inf;
		for(u = 2;u <= n;u++){
			for(j = 1;j <= n;j++){
				if(min > a[j][i] && min < a[i][u]){
					min = a[i][v];
					minx = j;
					miny = u;
				}
			}
				
		}
		book[minx][miny] = 1;
//		if(min == temp){
//			printf("not found");
//			return 0;
//		}
	}
	printf("%d %d %d",minx,miny,min);
	return 0;
}

