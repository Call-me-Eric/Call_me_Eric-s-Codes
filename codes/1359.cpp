#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int a[20][20] = {
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,-1},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}, ans;
int main() {
	for(int i = 1;i <= 10;i++){
		for(int j = 1;j <= 10;j++){
			scanf("%d",&a[i][j]);
		}
	}
	
	for(int i = 1;i <= 10;i++){
		for(int j = 1;j <= 10;j++){
			if(a[i][j] != 1 && (a[i + 1][j] == -1 || a[i - 1][j] == -1 
			|| a[i][j + 1] == -1 || a[i][j - 1] == -1))
			a[i][j] = -1;
		}
	}
	for(int i = 1;i <= 10;i++){
		for(int j = 1;j <= 10;j++){
			if(a[i][j] != 1 && (a[i + 1][j] == -1 || a[i - 1][j] == -1 
			|| a[i][j + 1] == -1 || a[i][j - 1] == -1))
			a[i][j] = -1;
		}
	}
	for(int i = 1;i <= 10;i++){
		for(int j = 1;j <= 10;j++){
			if(a[i][j] == 0)ans++;
		} 
	}
	printf("%d",ans);
	return 0;
}

