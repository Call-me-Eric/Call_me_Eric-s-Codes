#include <iostream>
#include <cstdio>
using namespace std;

struct bfs{
	int x, y, s;
};
int head = 1, tail = 1;bfs que[10001];
int n, m, startx, starty, endx, endy;
int x, y, flag;
int a[101][101], book[101][101];
const int Next[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int main(){
	scanf("%d%d",&n,&m);scanf("%d%d",&startx,&starty);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	
	book[startx][starty] = 1;
	que[tail].x = startx;
	que[tail].y = starty;
	que[tail].s = 0;
	tail++;
	while(head < tail){
		for(int i = 0;i <= 3;i++){
			
			x = que[head].x + Next[i][0];
			y = que[head].y + Next[i][1];
			
			if(x < 1 || x > n || y < 1 || y > m)continue;
			if(a[x][y] == 0 || book[x][y] == 1)continue;
			
			book[x][y] = 1;
			que[tail].x = x;
			que[tail].y = y;
			que[tail].s = que[head].s + 1;
			tail++;
		}
		head++;
	}
	printf("%d",tail - 1);
	return 0;
}

