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
const int next[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	scanf("%d%d%d%d",&startx,&starty,&endx,&endy);
	book[startx][starty] = 1;
	que[tail].x = startx;
	que[tail].y = starty;
	que[tail].s = 0;
	tail++;
	while(head < tail){
		for(int i = 0;i <= 3;i++){
			
			x = que[head].x + next[i][0];
			y = que[head].y + next[i][1];
			
			if(x < 1 || x > n || y < 1 || y > m)continue;
			if(a[x][y] == 1 || book[x][y] == 1)continue;
			
			book[x][y] = 1;
			que[tail].x = x;
			que[tail].y = y;
			que[tail].s = que[head].s + 1;
			tail++;
			
			if(x == endx && y == endy){
				flag = 1;
				break;
			}
		}
		if(flag)break;
		head++;
	}
	if(flag)printf("%d",que[tail - 1].s);
	else printf("No Way!");
	return 0;
}

