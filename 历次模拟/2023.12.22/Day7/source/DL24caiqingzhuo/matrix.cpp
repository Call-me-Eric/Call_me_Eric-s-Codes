#include <bits/stdc++.h>
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

const int N = 1010;
int n, m, k;

struct matrix
{
	int x, y;
	int a[N][N];
	void init()
	{
		memset(a, 0, sizeof(a));
	}
};

matrix mx, b;

void print(matrix a)
{
	for(int i = 1; i <= a.x; i = i + 1)
	{
		for(int j = 1; j <= a.y; j = j + 1)
			cout << a.a[i][j];
	}
	cout << "\n";
}

matrix operator * (const matrix a, const matrix b)
{
	matrix c;
	c.init();
	c.x = a.x;
	c.y = b.y;
	for(int i = 1; i <= c.x; i = i + 1)
		for(int j = 1; j <= a.y; j = j + 1)
			for(int k = 1; k <= c.y; k = k + 1)
			{
//				cout << (a.a[i][j] && b.a[j][k]) << "\n";
				c.a[i][k] ^= (a.a[i][j] && b.a[j][k]);
//				cout << c.a[i][k] << "\n";
			}
//	print(c);
	return c;
}

matrix csh()
{
	matrix a;
	a.x = n;
	a.y = n;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= n; j = j + 1)
		{
			if(i == j)
				a.a[i][j] = 1;
			else
				a.a[i][j] = 0;
		}
	return a;
}

matrix qp(matrix a, int b)
{
	matrix ans = csh(), tmp = a;
//		print(tmp * tmp);
//		cout << "!!!!\n";
//	ans.x = a.x, ans.y = a.y;
	while(b)
	{
		if(b & 1)
			ans = ans * tmp;
		tmp = tmp * tmp;
//		cout << "???\n";
		b >>= 1;
	}
	return ans;
}

signed main()
{
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	n = read();
	mx.x = n;
	mx.y = n;
	b.x = n;
	b.y = 1;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= n; j = j + 1)
		{
			char c = ' ';
			while(c != '0' && c != '1')
				c = getchar();
			mx.a[i][j] = c - '0';
		}
//	print(mx * mx);
	for(int i = 1; i <= n; i = i + 1)
	{
		char c = ' ';
		while(c != '0' && c != '1')
			c = getchar();
		b.a[i][1] = c - '0';
	}
	m = read();
	while(m --)
	{
		k = read();
		print(qp(mx, k) * b);
	}
	return 0;
}
