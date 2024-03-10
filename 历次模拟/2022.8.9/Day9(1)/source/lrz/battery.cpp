#include <cstdio>
#include <stack>
#include <cstring>

const int MAXN = 50;
const int MAXM = 50;

int n, m;
char s[2 * MAXN + 10][2 * MAXM + 10];

int head[2 * MAXN * MAXM + 10], numEdge;
struct Edge {
	int nxt, to;
}edge[2000010];

void addEdge(int x, int y) {

	++numEdge;
	edge[numEdge].nxt = head[x];
	edge[numEdge].to = y;
	head[x] = numEdge;

	return;
}

int get(int x, int y) {
	return (x - 1) * m + y;
}

int dfn[2 * MAXN + 10], low[2 * MAXN + 10], scc[2 * MAXN + 10], numScc, cnt;
std::stack<int>sta;

void tarjan(int u) {

	dfn[u] = low[u] = ++cnt;
	sta.push(u);
	for(int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if(!dfn[k]) {
			tarjan(k);
			low[u] = std::min(low[u], low[k]);
		}
		else if(!scc[k]) {
			low[u] = std::min(low[u], dfn[k]);
		}
	}

	if(dfn[u] == low[u]) {
		int t;
		++numScc;
		do {
			scc[t = sta.top()] = numScc;
			sta.pop();
		}while(t != u);
	}

	return;
}

struct Memory {
	int dx, dy;
	bool vis;
	int check;
}f[60][60][5];

Memory dfs(int x, int y, int dir) {

	if(f[x][y][dir].vis) {
		return f[x][y][dir];
	}
	f[x][y][dir].vis = true;
	
	int nx, ny;
	switch(dir) {
		case 1: nx = x, ny = y - 1; break;
		case 2: nx = x, ny = y + 1; break;
		case 3: nx = x - 1, ny = y; break;
		case 4: nx = x + 1, ny = y; break;
	}
		
	//第x行第y列 
	if(nx < 1 || nx > n || ny < 1 || ny > m) {
		return f[x][y][dir] = (Memory){0, 0, true, 0};
	}
	
	switch(s[nx][ny]) {
		case '.': return f[x][y][dir] = dfs(nx, ny, dir);
		case '-': return f[x][y][dir] = (Memory){nx, ny, true, 1};
		case '|': return f[x][y][dir] = (Memory){nx, ny, true, 1};
		case '#': return f[x][y][dir] = (Memory){nx, ny, true, 0};
		case '\\': return f[x][y][dir] = dfs(nx, ny, dir + (dir > 2 ? -2 : 2));
		case '/': return f[x][y][dir] = dfs(nx, ny, (dir == 1 ? 4 : (dir == 2 ? 3 : (dir == 3 ? 2 : 1))));
	}
}

int state[100][100];

void solve() {

	//炮台打炮台 
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '-' || s[i][j] == '|') {
				Memory res1 = dfs(i, j, 1);
				Memory res2 = dfs(i, j, 2);
				Memory res3 = dfs(i, j, 3);
				Memory res4 = dfs(i, j, 4);
				//自己打自己
				if((res1.check == -1 || res2.check == -1) && (res3.check == -1 || res4.check == -1)) {
					puts("IMPOSSIBLE");
					return;
				}
				//1表示只能将炮台竖着 
				if(res1.check == -1 || res2.check == -1) {
					state[i][j] = 1;
				}
				//0表示只能将炮台横着
				if(res3.check == -1 || res4.check == -1) {
					state[i][j] = 0;
				} 
				//自己打别人 
				if((res1.check == 1 || res2.check == 1) && (res3.check == 1 || res4.check == 1)) {
					puts("IMPOSSIBLE");
					return;
				}
				if(res1.check == 1 || res2.check == 1) {
					state[i][j] = 1;
				}
				if(res3.check == 1 || res4.check == 1) {
					state[i][j] = 0;
				}
			}
		}
	}
	
	//炮台打空地
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '.') {
				Memory res1 = dfs(i, j, 1);
				Memory res2 = dfs(i, j, 2);
				Memory res3 = dfs(i, j, 3);
				Memory res4 = dfs(i, j, 4);
				bool can1 = false, can2 = false, can3 = false, can4 = false;
				int tot = 0;
				if(res1.check == 1 && (state[res1.dx][res1.dy] == -1 || state[res1.dx][res1.dy] == 0)) {
					can1 = true; ++tot;
				}
				if(res2.check == 1 && (state[res2.dx][res2.dy] == -1 || state[res2.dx][res2.dy] == 0)) {
					can2 = true; ++tot;
				}
				if(res3.check == 1 && (state[res3.dx][res3.dy] == -1 || state[res3.dx][res3.dy] == 1)) {
					can3 = true; ++tot;
				}
				if(res4.check == 1 && (state[res4.dx][res4.dy] == -1 || state[res4.dx][res4.dy] == 1)) {
					can4 = true; ++tot;
				}
				if(tot == 0) {
					puts("IMPOSSIBLE");
					return;
				}
				if(tot == 1) {
					if(can1) state[res1.dx][res1.dy] = 0;
					if(can2) state[res2.dx][res2.dy] = 0;
					if(can3) state[res3.dx][res3.dy] = 1;
					if(can4) state[res4.dx][res4.dy] = 1;
				}
			}
		}
	}
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '.') {
				Memory res1 = dfs(i, j, 1);
				Memory res2 = dfs(i, j, 2);
				Memory res3 = dfs(i, j, 3);
				Memory res4 = dfs(i, j, 4);
				bool can1 = false, can2 = false, can3 = false, can4 = false;
				int tot = 0;
				if(res1.check == 1 && (state[res1.dx][res1.dy] == -1 || state[res1.dx][res1.dy] == 0)) {
					can1 = true; ++tot;
				}
				if(res2.check == 1 && (state[res2.dx][res2.dy] == -1 || state[res2.dx][res2.dy] == 0)) {
					can2 = true; ++tot;
				}
				if(res3.check == 1 && (state[res3.dx][res3.dy] == -1 || state[res3.dx][res3.dy] == 1)) {
					can3 = true; ++tot;
				}
				if(res4.check == 1 && (state[res4.dx][res4.dy] == -1 || state[res4.dx][res4.dy] == 1)) {
					can4 = true; ++tot;
				}
				if(tot == 2) {
					if(can1 && can3 && state[res1.dx][res1.dy] == -1 && state[res3.dx][res3.dy] == -1) {
						addEdge(n * m + get(res1.dx, res1.dy), n * m + get(res3.dx, res3.dy));
						addEdge(get(res3.dx, res3.dy), get(res1.dx, res1.dy));
					}
					if(can1 && can4 && state[res1.dx][res1.dy] == -1 && state[res4.dx][res4.dy] == -1) {
						addEdge(n * m + get(res1.dx, res1.dy), n * m + get(res4.dx, res4.dy));
						addEdge(get(res4.dx, res4.dy), get(res1.dx, res1.dy));
					}
					if(can3 && can2 && state[res2.dx][res2.dy] == -1 && state[res3.dx][res3.dy] == -1) {
						addEdge(n * m + get(res3.dx, res3.dy), n * m + get(res2.dx, res2.dy));
						addEdge(get(res2.dx, res2.dy), get(res3.dx, res3.dy));
					}
					if(can4 && can2 && state[res2.dx][res2.dy] == -1 && state[res4.dx][res4.dy] == -1) {
						addEdge(n * m + get(res4.dx, res4.dy), n * m + get(res2.dx, res2.dy));
						addEdge(get(res2.dx, res2.dy), get(res4.dx, res4.dy));
					}
				}
			}
		}
	}
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '-' || s[i][j] == '|') {
				if(!dfn[get(i, j)]) {
					tarjan(get(i, j));
				}
			}
		}
	}
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '-' || s[i][j] == '|') {
				if(scc[get(i, j)] == scc[get(i, j) + n * m]) {
					puts("IMPOSSIBLE");
					return;
				}
			}
		}
	}
	puts("POSSIBLE");
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(s[i][j] == '-' || s[i][j] == '|') {
				if(state[i][j] == 0) {
					putchar('-');
				}
				else if(state[i][j] == 1) {
					putchar('|');
				}
				else {
					if(scc[get(i, j)] > scc[get(i, j) + n * m]) {
						putchar('-');
					}
					else {
						putchar('|');
					}
				}
			}
			else {
				printf("%c", s[i][j]);
			}
		}
		puts("");
	}

	return;
}

int main() {

	freopen("battery.in", "r", stdin);
	freopen("battery.out", "w", stdout);

	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%s", s[i] + 1);
		}
		
		numEdge = 0;
		std::memset(head, 0, sizeof(head));
		std::memset(low, 0, sizeof(low));
		std::memset(dfn, 0, sizeof(dfn));
		std::memset(scc, 0, sizeof(scc));
		cnt = 0, numScc = 0;
		while(!sta.empty()) {
			sta.pop();
		}
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j) {
				state[i][j] = -1;
				for(int k = 1; k <= 4; ++k) {
					f[i][j][k] = (Memory){0, 0, false, -1};
				}
			}
		}
		
		solve();
	}

	return 0;
}
