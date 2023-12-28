# include <bits/stdc++.h>

using namespace std;

# define ll long long
# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second
# define pb push_back

int read()
{
# define C ch = getchar()
	int x = 0; char C;
	for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

const int N = 510 , mod = 998244353;
int n , q , a[N][N] ,  ans , vis[N][N];
int dx[4] = {1 , -1 , 0 , 0};
int dy[4] = {0 , 0 , 1 , -1};

void dfs(int x , int y , int t)
{
	ans++ , ans %= mod;
	if(t > a[x][y]) return ;
	for(int i = 0; i < 4; i++)
	{
		int nx = x + dx[i] , ny = y + dy[i];
		if(nx >= 1 && nx <= n && ny >= 1 && ny <= n)
		{
			dfs(nx , ny , a[x][y] + 1); 
		} 
	}
}

void work()
{
	ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			vis[i][j] = 1;
			dfs(i , j , 0);
			vis[i][j] = 0;
		}
	}
	cout << ans << endl;
}

int main()
{
	freopen("grid.in" , "r" , stdin);
	freopen("grid.out" , "w" , stdout);
	n = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) a[i][j] = read();
	q = read();
	for(int i = 1 , x , y; i <= q; i++)
	{
		x = read() , y =  read();
		int tmp = a[x][y];
		a[x][y] = -1e9;
		work();
		a[x][y] = tmp;
	}
	return 0;
}
