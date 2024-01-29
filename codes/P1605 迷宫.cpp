#include <iostream>
#include <cstdio>

using namespace std;
int n, m, t, a[10][10],ans;
int sx, sy, ex, ey, x1, y1;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};  
void dfs(int x, int y){
	if(x == ex && y == ey){
		ans++;	return;
	}
	else{
		for(int i = 0; i < 4; i++){
			int xx =x + dx[i], yy = y +dy[i]; 
			if(xx >= 1 && xx <=n && yy >= 1 && yy <= n)
				if(!a[xx][yy]){
					a[xx][yy] = 1;
					dfs(xx, yy);
					a[xx][yy] = 0;
				}
		}
		return;
	}
}
int main(){
	scanf("%d%d%d", &n, &m, &t);
	scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
	for(int i = 1; i <= t; i++){
		scanf("%d%d", &x1, &y1);
		a[x1][y1] = 1;
	}
	a[sx][sy] = 1; 
	dfs(sx, sy);
	printf("%d", ans);
	return 0;
}

