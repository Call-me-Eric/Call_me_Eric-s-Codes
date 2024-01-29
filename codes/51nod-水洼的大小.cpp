#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
char c[1000][1000];
int p[1000][1000];
bool book[1000][1000];
int nx[4] = {0,0,1,-1};
int ny[4] = {1,-1,0,0};
int a;
int n,m;
int ans;
int num[1000000];
void dfs(int x,int y){
	book[x][y] = 1;
	p[x][y] = ans;
	num[ans]++;
	for(int k = 0;k < 4;k++){
		int i = x + nx[k];
		int j = y + ny[k];
		if(i >= 0 && i < n && j >= 0 && j < m && c[i][j] == '.' && book[i][j] == 0){
			dfs(i,j);
		}
	}
}
int tot = 0;
int w[10];
int main(){
	scanf("%d%d",&n,&m);
	getchar();
	for(int i = 0;i < n;i++){
		scanf("%s",c[i]);
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(c[i][j] == '.' && !book[i][j]){
				dfs(i,j);
				ans++;
			}
		}
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			if(c[i][j] == '.')putchar('.');
			else{
				tot = 0;
				for(int k = 0;k < 4;k ++){
					int x = i + nx[k];
					int y = j + ny[k];
					if(x >= 0 && x < n && y >= 0 && y < m && c[x][y] == '.'){
						w[tot++] = p[x][y];
					}
				}
				sort(w,w + tot);
				tot = unique(w,w + tot) - w;
				int tmp = 1;
				for(int k = 0;k < tot;k++){
					tmp += num[w[k]];
				}
				printf("%d",tmp % 10);
			}
		}
		putchar('\n');
	}
	return 0;
}

