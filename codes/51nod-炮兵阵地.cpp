#include<iostream>
#include<cstdio>
using namespace std;
int n;
char c[5][5],b[5][5];
int ans = 0;
bool book[5][5];
void dfs(int x,int y,int tot){
	if(tot > ans)ans = tot;
	b[x][y] = 'X';
	int i1, i2, i3, i4;
	for(i1 = x + 1;i1 <= n && b[i1][y] == '.';i1++){
		b[i1][y] = 'X';
	}
	for(i2 = x - 1;i2 >= 1 && b[i2][y] == '.';i2--){
		b[i2][y] = 'X';
	}
	for(i3 = y + 1;i3 <= n && b[x][i3] == '.';i3++){
		b[x][i3] = 'X';
	}
	for(i4 = y - 1;i4 >= 1 && b[x][i4] == '.';i4--){
		b[x][i4] = 'X';
	}
	for(int i = x;i <= n;i++){
		for(int j = (i == x ? (y + 1) : 1);j <= n;j++){
			if(b[i][j] == 'X')continue;
			dfs(i,j,tot + 1);
		}
	}
	for(int i = i2 + 1;i < i1;i++){
		b[i][y] = '.';
	}
	for(int j = i4 + 1;j < i3;j++){
		b[x][j] = '.';
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%s",c[i] + 1);
		for(int j = 1;j <= n;j++){
			b[i][j] = c[i][j];
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(c[i][j] == 'X')continue;
			dfs(i,j,1);
		}
	}
	printf("%d",ans);
	return 0;
}

