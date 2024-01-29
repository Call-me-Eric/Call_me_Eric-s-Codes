#include <iostream>
#include <cstdio>
#include <queue>
#define for1(i, a, b) for(int i = a; i <= b; i++)  //简写for循环， 
using namespace std;

struct Node{
	int x, y;
};

const int N = 1005;
const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0, 0, -1};
char G[N][N];
int  c[N][N];
int  cnt[N * N];
int n, m, color = 1;

bool pd(int x, int y){
	return x >=1 && x <= n && y >= 1 && y <= n;
}

void bfs(int s, int t){
	queue<Node> q;
	q.push((Node){s, t});
	c[s][t] = color;
	cnt[color] ++;
	while(!q.empty()){
		Node u = q.front();
		q.pop();
		int x = u.x, y = u.y;
		for1(i, 0, 3){
			int xx = x+dx[i], yy = y + dy[i];
			if(pd(xx, yy) && G[x][y] != G[xx][yy] && c[xx][yy] == 0){
				c[xx][yy] = color;
				cnt[color]++;
				q.push((Node){xx, yy});
			}
		}
		
	}
}

int main(){
	ios::sync_with_stdio(false); //加速cin cout读取速度 
	cin >> n >> m;
	for1(i, 1, n)
		for1(j, 1, n)
			cin >> G[i][j];
	int x, y;
	for1(i, 1, m){
		cin >> x >>y;
		color = i;
		if(c[x][y] == 0)	bfs(x,y);
		cout << cnt[c[x][y]] << endl;
	}
	return 0;
}

