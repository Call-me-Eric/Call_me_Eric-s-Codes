#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	int a = 0;
	while(c >= '0' && c <= '9')
	{
		a = a * 10 + c - '0';
		c = getchar();
	}
	return a;
}

int a[61][61];
int dan[3000];

const int mod = 998244353;

struct pos
{
	int x;
	int y;
};
pos to[3000];

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int tak = 1, nx, ny;

int m, tp;

signed main()
{
	freopen("maze.in", "r", stdin);
	freopen("maze.out", "w", stdout);
	a[30][30] = 1;
	nx = 30, ny = 30;
	to[1].x = 30, to[1].y = 30;
	for(int cnt = 1; tak <= 2500; cnt ++)
	{
		int tt = (cnt + 1) / 2;
		for(int t = 1; t <= tt; t ++)
		{
			nx += dx[cnt % 4];
			ny += dy[cnt % 4];
			a[nx][ny] = ++ tak;
			to[tak].x = nx, to[tak].y = ny;
		}
	}
	m = read();
	tp = read();
	while(m --)
	{
		int op;
		op = read();
		if(op == 1)
		{
			int l, r, v;
			l = read();
			r = read();
			v = read();
			for(int i = l; i <= r; i = i + 1)
				dan[i] += v;
		}
		if(op == 2)
		{
			int x, v;
			x = read();
			v = read();
			int px = to[x].x;
			int py = to[x].y;
			for(int i = min(px, to[1].x); i <= max(px, to[1].x); i = i + 1)
				for(int j = min(py, to[1].y); j <= max(py, to[1].y); j = j + 1)
					dan[a[i][j]] += v;
		}
		if(op == 3)
		{
			int l, r, all = 0;
			l = read();
			r = read();
			for(int i = l; i <= r; i = i + 1)
				all += dan[i];
			cout << all % mod << "\n";
		}
	}
	return 0;
}
