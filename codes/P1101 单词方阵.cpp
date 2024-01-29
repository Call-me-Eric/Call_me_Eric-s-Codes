#include <iostream>
#include <cstdio>

using namespace std;
char map[101][101];
char txt[8]= "yizhong";
bool vis[101][101];
int n; 
int dx[] ={0,0,1,1,1,-1,-1,-1};
int dy[] ={1,-1,1,0,-1,-1,0,1};
void dfs(int x, int y, int s){
	if(s== 8) {
		return;
	}
	if(map[x][y] == txt[s] && !vis[x][y]){
		vis[x][y] = 1;
		for(int i = x; i <= n; i++)
			for(int j = y; j <= n; j++){
				int nx = x+dx[i], ny = y+dy[j];
				dfs(nx,ny,s+1);
			}
		}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i =1 ; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> map[i][j];
	dfs(1,1,0);
	return 0;
}

