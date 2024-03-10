#include <bits/stdc++.h>

using namespace std;
FILE *fin, *fout, *fstd, *fscr, *frpt;

const int maxn = 505;
char e[maxn][maxn], mp[maxn][maxn]; int n, m, T, Tt;
bool cov[maxn][maxn];

bool inG(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
void WA(int type) {
	fprintf(fscr, "0");
	fprintf(frpt, "Wrong Answer[%d] in Case %d", type, Tt);
	exit(0);
}
int type(char c) {
	if (c == '.') return 1;
	if (c == '#') return 2;
	if (c == '/') return 3;
	if (c == '\\') return 4;
	if (c == '-') return 5;
	if (c == '|') return 5;
	return 0;
}
bool test(FILE *fin)
{
	fscanf(fin, "%s", e[0]);
	if (e[0][0] == 'I') return false;
	for (int i = 1; i <= n; i++)
		fscanf(fin, "%s", e[i] + 1);
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	{
		if (!type(e[i][j])) WA(1);
		if (type(e[i][j]) != type(mp[i][j])) WA(2);
	}
	return true;
}
void cover(int x, int y, int d)
{
	x += dx[d]; y += dy[d];
	if (!inG(x, y)) return ;
	if (type(e[x][y]) == 2) return ;
	if (type(e[x][y]) == 5) WA(4);
	cov[x][y] = true;
	if (type(e[x][y]) == 3) d = 1 ^ d;
	if (type(e[x][y]) == 4) d = 3 ^ d;
	cover(x, y, d);
}
int main(int argc, char **argv)
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "r");
	fstd = fopen(argv[3], "r");
	int scr = atoi(argv[4]);
	
	fscr = fopen(argv[5], "w");
	frpt = fopen(argv[6], "w");
	
	fscanf(fin, "%d", &T);
	
	for (Tt = 1; Tt <= T ; Tt++)
	{
		fscanf(fin, "%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			fscanf(fin, "%s", mp[i] + 1);
		bool x = test(fstd);
		
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) e[i][j] = 0;
		bool y = test(fout);
		if (x != y) WA(3);
		if (!x) continue;
		
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cov[i][j] = false;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		if (type(e[i][j]) == 5) {
			if (e[i][j] == '-') cover(i, j, 1), cover(i, j, 3);
			if (e[i][j] == '|') cover(i, j, 0), cover(i, j, 2);
		}
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (type(e[i][j]) == 1 && !cov[i][j]) WA(5);
	}
	
	fprintf(fscr, "%d", scr);
	fprintf(frpt, "Congratulations!");
}
