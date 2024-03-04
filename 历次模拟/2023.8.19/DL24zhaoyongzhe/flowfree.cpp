#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 13;
int n, m;
struct node{
	int x, y;
	node(int x = 0,int y = 0):x(x),y(y){}
	friend bool operator == (node a,node b){
		return a.x == b.x && a.y == b.y;
	}
}path[maxn][maxn * maxn], st[maxn], ed[maxn];
int book[maxn][maxn], len[maxn];
void putans(){
	for(int i = 1;i <= m;i++){
		printf("%d\n",len[i]);
		for(int j = 1;j <= len[i];j++){
			printf("%d %d\n",path[i][j].x, path[i][j].y);
		}
	}
}
void debug(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			printf("%.6d ",book[i][j]);
		}
		puts("");
	}
}

const int dx[5] = {0,1,-1,0, 0};
const int dy[5] = {0,0, 0,1,-1};
bool flag = false;
void dfs1(int x,int y,int col,int sum){
//	debug();
//	printf("%d %d %d %d\n",x,y,col,sum);
	if(col == m + 1){
		if(sum == n * n + 1){
			putans(); flag = 1;
		}
		return;
	}
	if(flag)return;
	path[col][++len[col]] = node(x,y);
	for(int i = 1;i <= 4 && !flag;i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(!(1 <= nx && nx <= n && 1 <= ny && ny <= n))continue;
		if(node(nx, ny) == ed[col]){
			path[col][++len[col]] = node(nx,ny);
			dfs1(st[col + 1].x,st[col + 1].y,col + 1,sum + 2);
			len[col]--;
			continue;
		}
		if(book[nx][ny] != 0)continue;
		book[nx][ny] = col;dfs1(nx,ny,col,sum + 1);book[nx][ny] = 0;
	}
	len[col]--;
}
signed main(){
//	freopen("flowfree.in","r",stdin);
//	freopen("flowfree.out","w",stdout);
	n = read(); m = read();int u, v;
	for(int i = 1;i <= m;i++){
		u = read(); v = read();
		st[i] = node(u, v); book[u][v] = -114514;
		u = read(); v = read();
		ed[i] = node(u, v); book[u][v] = -i;
	}
	dfs1(st[1].x,st[1].y,1,1);
	return 0;
}

