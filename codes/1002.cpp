#include <iostream>
#include <cstdio>
using namespace std;
int sum = 0,endx,endy,a,b;
int a[22][22],book[22][22];
int next[2][2] = {{0,1},{1,0}};
void dfs(int x,int y){
	sum++;
	if(x == endx && y == endy)	return;
	int tx = x,ty = y;
	for(int i = 0; i < 2; ++){
		tx = x+next[i][0];
		ty = y+next[i][1]; 
		if(tx < 0 || ty < 0 ||tx >endx ||ty >endy)
			continue;
		if(tx == -1 && ty == -1) //马能走的位置 
			continue;
		book[tx][ty] = 1;
		dfs(tx,ty);
		book[tx][ty] = 0; 
		
	}
	return ;
	
} 
int main(){
	scanf("%d%d%d%d",&endx, &endy, &a, &b);
	
	book[0][0]=1;
	dfs(0,0);
	printf("%d\n",sum);
	return 0;
}

