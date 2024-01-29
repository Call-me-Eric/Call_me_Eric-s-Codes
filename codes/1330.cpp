#include <cstdio>
#include <iostream>
#include <cstring>
#define wendl (putchar(10))
using namespace std;
inline int qread(){
	char ch;int k = 1, t = 0;
	while ( !isdigit( ch = getchar() ) ){
		if (ch == EOF) return -1;
		if (ch == '-') k = -1;
	}
	t = ch - '0';
	while ( isdigit( ch = getchar() ) ) t = t * 10 + ch - '0';
	return k * t;
}
inline void data(int k){
	if(k > 9)data(k / 10);
	putchar(k % 10 + '0');
}
inline void qwrite(int k){
	if(k < 0){
		k = -k;
		putchar('-');
	}
	data(k);
}
struct intt{
	int x, y, s;
}b[111 * 112];
bool book[111][111];
int go[12][2] = {{2, -1}, {2, 1}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {-1, -2}, {1, -2}, 
														{2, 2}, {-2, 2}, {2, -2}, {-2, -2}};
int n, m;
void bfs(int endx,int endy){
	int head = 1, tail = 2;
	b[head].x = 1;b[head].y = 1;b[head].s = 0;
	intt t;
		while(head < tail){
			for(int i = 0;i < 12;i++){
				t.x = b[head].x + go[i][0];
				t.y = b[head].y + go[i][1];
				if(!(t.x < 1 || t.x > 100 || t.y < 1 || t.y > 100 || book[t.x][t.y])){
					b[tail].x = t.x;
					b[tail].y = t.y;
					b[tail].s = b[head].s + 1;
					book[t.x][t.y] = true;
					if(b[tail].x == endx && b[tail].y == endy){
						printf("%d\n",b[tail].s);
						return ;
					}
					tail++;
				}
			} 
		head++;
		}
	return ;
}
int main() {
	scanf("%d%d",&n, &m);
	bfs(n, m);
	memset(book,0,sizeof(book));
	scanf("%d%d",&n, &m);
	bfs(n, m);
	return 0;
}

