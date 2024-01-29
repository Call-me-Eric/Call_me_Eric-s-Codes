#include <cstdio>
using namespace std;

struct note{int x, y;};

int head = 1, tail = 1;note que[2501];
int n, m, x, y, t, tx, ty, max;
char a[51][51];bool book[51][51];
const int Next[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int getnum(int x, int y){
	int i, j, sum = 0;
	i = x;j = y;
	while(a[i][j] != '#'){
		if(a[i][j] == 'G')
			sum++;
		i--;
	}
	i = x;j = y;
	while(a[i][j] != '#'){
		if(a[i][j] == 'G')
			sum++;
		i++;
	}
	i = x;j = y;
	while(a[i][j] != '#'){
		if(a[i][j] == 'G')
			sum++;
		j--;
	}
	i = x;j = y;
	while(a[i][j] != '#'){
		if(a[i][j] == 'G')
			sum++;
		j++;
	}
	return sum;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i = 0;i < n;i++) scanf("%s",a[i]);
	book[x][y] = 1;
	que[tail].x = x;
	que[tail].y = y;
	max = getnum(x,y);
	tail++;
	while(head < tail){
		for(int i = 0;i <= 3;i++){
			tx = que[head].x + Next[i][0];
			ty = que[head].y + Next[i][1];
			if(tx < 0 || tx > n - 1 || ty < 0 || ty > m - 1)continue;
			if(book[tx][ty] == 1 || a[tx][ty] != '.')continue;
			book[tx][ty] = 1;
			que[tail].x = tx;
			que[tail].y = ty;
			tail++;
			t = getnum(tx,ty);
			if(t > max)max = t;
		}
		head++;
	}
	printf("%d",max);
	return 0;
}

