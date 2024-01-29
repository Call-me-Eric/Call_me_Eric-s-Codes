#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n;
int ans = 0;
int e[55][55];
char c[5][5];
bool book[55];
void init_(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			int pos = i * 10 + j;
			int k = i + 1;
			while(k <= n && c[k][j] != 'X')k++;
			while(k <= n)e[pos][k++ * 10 + j] = 1;
			k = i - 1;
			while(k >= 1 && c[k][j] != 'X')k--;
			while(k >= 1)e[pos][k-- * 10 + j] = 1;
			k = j + 1;
			while(k <= n && c[i][k] != 'X')k++;
			while(k <= n)e[pos][i * 10 + k++] = 1;
			k = j - 1;
			while(k >= 1 && c[i][k] != 'X')k--;
			while(k >= 1)e[pos][i * 10 + k--] = 1;
		}
	}
}
bool dfs(int pos){
	for(int i = 1;i <= n * 10 + n;i++){
		if(!book[i] && ){
			
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%s",c[i] + 1);
	}
	init_();
	for(int i = 1;i <= n * 10 + n;i++){
		memset(book,0,sizeof(book));
		if(c[(i - i / 10) / 10][i / 10] != 'X' && dfs(i)) ans++;
	}
	return 0;
}

