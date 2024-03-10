#include <bits/stdc++.h>
using namespace std; 
const int D[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}; 

int n, m; 
struct Node {
	int x, y; 
	Node(int x = 0, int y = 0) : x(x), y(y) {}
} a[15], b[15], path[15][225];
int col[15][15], tot[15]; 

void dfs(int p, int x, int y) {
	if (p > m) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (!col[i][j]) return; 
		for (int i = 1; i <= m; ++i) {
			printf("%d\n", tot[i] + 1); 
			for (int j = 1; j <= tot[i]; ++j)
				printf("%d %d\n", path[i][j].x, path[i][j].y); 
			printf("%d %d\n", b[i].x, b[i].y); 
		}
		exit(0); 
	}
	for (int k = 0; k < 4; ++k) {
		int xx = x + D[k][0], yy = y + D[k][1]; 
		if (xx < 1 || yy < 1 || xx > n || yy > n) continue; 
		if (col[xx][yy]) {
			if (xx == b[p].x && yy == b[p].y) dfs(p + 1, a[p + 1].x, a[p + 1].y); 
			continue; 
		}
		col[xx][yy] = p; path[p][++tot[p]] = Node(xx, yy); 
		dfs(p, xx, yy);  
		col[xx][yy] = 0; --tot[p]; 
	}
}

int main(void) {
	freopen("flowfree.in", "r", stdin); 
	freopen("flowfree.out", "w", stdout); 
	scanf("%d%d", &n, &m); 
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", &a[i].x, &a[i].y, &b[i].x, &b[i].y); 
		col[a[i].x][a[i].y] = i; 
		col[b[i].x][b[i].y] = i; 
		tot[i] = 1; path[i][1] = a[i]; 
	}
	dfs(1, a[1].x, a[1].y); 
	return 0; 
} 
