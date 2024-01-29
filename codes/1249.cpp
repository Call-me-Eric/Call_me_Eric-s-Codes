#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
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
	int x, y;
}b[111 * 112];
char a[111][111];
bool book[111][111];
int n, m, ans;
void bfs(int __x,int __y){
	int head = 1, tail = 2;
	int x, y;
	b[head].x = __x;b[head].y = __y;
	book[__x][__y] = true;
	while(head < tail){
		for(int i = -1;i <= 1;i++){
			for(int j = -1;j <= 1;j++){
				x = b[head].x + i;
				y = b[head].y + j;
				if(x < 1 || y < 1 || x > n || y > m)continue;
				if(!book[x][y] && a[x][y] == 'W'){
					b[tail].x = x;
					b[tail].y = y;
					book[x][y] = true;
					tail++;
				} 
			}
		}
		head++;
	}
	ans++;
}
int main() {
	scanf("%d%d",&n, &m);
	for(int i = 1;i <= n;i++){
		scanf("%s",a[i] + 1);
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(!book[i][j] && a[i][j] == 'W')bfs(i,j);
		}
	}
	printf("%d\n",ans);
	return 0;
}

