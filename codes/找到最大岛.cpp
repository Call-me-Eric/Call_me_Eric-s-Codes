#include <cstdio>
using namespace std;

struct bfs{
	int x, y;
};
int head = 1, tail = 1;bfs que[10001];
int x, y, n, m, Max;
int a[101][101], book[101][101];
const int Next[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(!book[i][j] && a[i][j] != 0){
				head = tail = 1;
				book[i][j] = 1;
				que[tail].x = i;
				que[tail].y = j;
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
						tail++;
					}
					head++;
				}
				if(tail - 1 > Max)Max = tail - 1;
			}
		}
	}
	printf("%d",Max);
	return 0;
}
