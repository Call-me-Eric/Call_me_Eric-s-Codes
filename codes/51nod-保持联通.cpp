#include<iostream>
#include<stdio.h>
using namespace std;
int n, m, k;
int s;
bool book[510][510];
char c[510][510];
void dfs(int x,int y){
	if(x < 0 || x >= n || y < 0 || y >= m)return;
	if(c[x][y] != '.' || book[x][y])return;
	book[x][y] = 1;s--;
	if(s < k)c[x][y] = 'X';
	dfs(x + 1,y);
	dfs(x,y - 1);
	dfs(x - 1,y);
	dfs(x,y + 1);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	getchar();
	for(int i = 0;i < n;i++){
		scanf("%s",c[i]);
		for(int j = 0;j < m;j++){
			s += c[i][j] == '.';
		}
		getchar();
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			dfs(i,j);
		}
	}
	for(int i = 0;i < n;i++){
		puts(c[i]);
	}
	return 0;
}

