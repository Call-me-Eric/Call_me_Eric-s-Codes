#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	int p = 0;
	while(c >= '0' && c <= '9')
		p = (p << 3) + (p << 1) + c - '0', c = getchar();
	return p;
}

char s[20];
inline void write(int x)
{
	if(x == 0)
		putchar('0');
	int i = 1;
	while(x)
	{
		s[i] = x % 10;
		x /= 10;
		i ++;
	}
	i --;
	while(i)
	{
		putchar(s[i] + '0');
		i --;
	}
	putchar(' ');
}

const int N = 30000;
int n, k;
int m, tmp;

struct edge
{
	int ed;
	int len;
};

vector <edge> e[N];

void add(int st, int ed, int len)
{
	e[st].push_back((edge){ed, len});
}

int dis[N];
bool vis[N];

struct node
{
	int ed;
	int len;
	bitset <12> f;
};

node S;

void spfa()
{
	memset(dis, 0x3f3f3f, sizeof(dis));
	queue <node> q;
	S.ed = 1;
	S.len = 0;
	q.push(S);
	dis[1] = 0;
	while(!q.empty())
	{
		node t = q.front();
		int st = t.ed;
		int ss = (st + n - 1) / n;
		q.pop();
		for(int i = 0; i < e[st].size(); i = i + 1)
		{
			int ed = e[st][i].ed;
			int len = e[st][i].len;
			int se = (ed + n - 1) / n;
			if(ed > n && t.f[se] == 1 && ss != se)
				continue;
			if(dis[ed] > dis[st] + len)
			{
				dis[ed] = dis[st] + len;
				t.f[se] = 1;
				q.push((node){ed, dis[ed], t.f});
				t.f[se] = 0;
			}
		}
	}
}

signed main()
{
	freopen("subway.in", "r", stdin);
	freopen("subway.out", "w", stdout);
	n = read();
	k = read();
	for(int i = 1; i <= k; i = i + 1)
	{
		for(int j = 1; j <= n; j = j + 1)
		{
			tmp = read();
			add(j, i * n + j, tmp);
		}
		for(int j = 1; j <= n; j = j + 1)
		{
			tmp = read();
			add(i * n + j, j, tmp);
		}
		m = read();
		for(int j = 1; j <= m; j = j + 1)
		{
			int st, ed, len;
			st = read();
			ed = read();
			len = read();
			add(i * n + st, i * n + ed, len);
			add(i * n + ed, i * n + st, len);
		}
	}
	spfa();
	write(dis[n]);
//	for(int i = 1; i <= (n + 1) * k; i = i + 1)
//		write(dis[i]);
	return 0;
}
