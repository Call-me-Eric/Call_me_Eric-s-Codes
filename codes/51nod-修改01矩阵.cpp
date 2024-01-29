#include<iostream>
#include<cstdio>
using namespace std;
bool a[21][21],b[21][21];
int n;
bool ans = false;
void doit(int x,int y){
	if(x == 0 || y == 0)return;
	a[x][y] = !a[x][y];
	if(x > 1)a[x - 1][y] = !a[x - 1][y];
	if(x < n)a[x + 1][y] = !a[x + 1][y];
	if(y > 1)a[x][y - 1] = !a[x][y - 1];
	if(y < n)a[x][y + 1] = !a[x][y + 1];
}

void dfs(int pos){
	if(pos == n + 1){
		for(int i = 2;i <= n;i++){
			for(int j = 1;j <= n;j++){
				if(a[i - 1][j])	doit(i,j);
			}
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				if(a[i][j])	return;
			}
		}
		printf("Yes");
		exit(0);
	}
	doit(1,pos);
	dfs(pos + 1);
	doit(1,pos);
	dfs(pos + 1);
}
int main(){
	scanf("%d",&n);
	int k = 0;
	bool tmp1 = true;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			scanf("%d",&k);
			b[i][j] = a[i][j] = k;
		}
	}
	dfs(1);
	puts("No");
	return 0;
}

