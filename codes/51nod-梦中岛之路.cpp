#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
int a[200][200];
int p[2][100000][2];
int n;
int cnt[2];
int r;
int ans;
int next_[4][2] = {0,1,0,-1,1,0,-1,0};
void dfs(int t,int x,int y){
	a[x][y] = 0;
	p[t][cnt[t]][0] = x;
	p[t][cnt[t]++][1] = y;
	int nx = 0, ny = 0;
	for(int i = 0;i < 4;i++){
		nx = next_[i][0] + x;
		ny = next_[i][1] + y;
		if(a[nx][ny]){
			dfs(t,nx,ny);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			scanf("%1d",&a[i][j]);
		}
	}
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(a[i][j]){
				dfs(r,i,j);
				r++;
			}
		}
	}
	ans = 99999999;
	for(int i = 0;i < cnt[0];i++){
		for(int j = 0;j < cnt[1];j++){
			ans = min(ans,abs(p[0][i][0] - p[1][j][0]) + abs(p[0][i][1] - p[1][j][1]));
		}
	}
	printf("%d",ans - 1);
	return 0;
}

