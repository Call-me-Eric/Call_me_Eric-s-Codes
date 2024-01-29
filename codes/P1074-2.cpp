#include<cstdio>
#include<iostream>
using namespace std;
int ans = -1;
int a[10][10];
int b[10][10];
bool x[10][10],y[10][10],z[10][10];
//标记数组：x[i][j]==1是第i行j数字已被用，y[i][j]==1是第i列j数字已被用
//			z[i][j]==1是第i个宫j数字已被用
int score[10][10] = {
{0,0,0,0,0,0 ,0,0,0,0},
{0,6,6,6,6,6 ,6,6,6,6},
{0,6,7,7,7,7 ,7,7,7,6},
{0,6,7,8,8,8 ,8,8,7,6},
{0,6,7,8,9,9 ,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9 ,9,8,7,6},
{0,6,7,8,8,8 ,8,8,7,6},
{0,6,7,7,7,7 ,7,7,7,6},
{0,6,6,6,6,6 ,6,6,6,6},
};
int gong(int i,int j){
	int x1 = (i % 3)? (i / 3) : (i / 3 - 1);
	int y1 = (j % 3)? (j / 3 + 1) : (j / 3);
	return x1 * 3 + y1;
} 
void dfs(int i,int j){
	if(i == 9 && j == 10){
		int tmp = 0;
		for(int i = 1;i <= 9;i++)
			for(int j = 1;j <= 9;j++)
				tmp += score[i][j] * a[i][j];
    	ans = max(tmp,ans);
		return;
	}
	if(j > 9){
		dfs(i + 1,1);
		return;
	}
	if(b[i][j] != 0){
		dfs(i,j + 1);
		return;
	}
	for(int k = 1;k <= 9;k++){
		if( !( x[i][k] || y[j][k] || z[gong(i,j)][k]) ){
			b[i][j] = k;
			x[i][k] = y[j][k] = z[gong(i,j)][k] = 1;
			dfs(i,j + 1);
			b[i][j] = 0;
			x[i][k] = y[j][k] = z[gong(i,j)][k] = 0;
		}
	}
}
int main(){
	for(int i = 1;i <= 9;i++){
		for(int j = 1;j <= 9;j++){
			scanf("%d",&a[i][j]);
			b[i][j] = a[i][j];
			if(a[i][j] != 0){
				x[i][a[i][j]] = 1;
				y[j][a[i][j]] = 1;
				z[gong(i,j)][a[i][j]] = 1;
			}
		}
	}
	dfs(1,1);
	printf("%d",ans);
	return 0;
}
