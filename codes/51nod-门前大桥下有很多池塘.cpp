#include<iostream>
#include<stdio.h>
using namespace std;
char c[310][310];
int n,m;
int ans;
void dfs(int x,int y){
	c[x][y] = '.';
	for(int nx = -1;nx <= 1;nx++){
		for(int ny = -1;ny <= 1;ny++){
			int i = x + nx;
			int j = y + ny;
			if(i >= 0 && i < n && j >= 0 && j < m && c[i][j] == 'W'){
				dfs(i,j);
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	getchar();
	for(int i = 0;i < n;i++){
		scanf("%s",c[i]);
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(c[i][j] == 'W'){
				dfs(i,j);
				ans++;
			}
		}
	}
	printf("%d",ans);
	return 0;
}

