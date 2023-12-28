#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define eb emplace_back
#define pb pop_back
#define endl '\n'
#define mid (l+r>>1)
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pii pair<int,int>
#define fi first
#define se second
#define getchar() cin.get()
int dx[4] = { 1 , 0 , -1 , 0 };
int dy[4] = { 0 , 1 , 0 , -1 };
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 500 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , q , a[N][N];

struct node { int x , y , tim; };

int check ( int x , int y ) { return 1 <= x && x <= n && 1 <= y && y <= n; }

int bfs ( int sx , int sy )
{
	queue<node> q;
	int cnt = 0;
	q.push ( { sx , sy , 0 } );
	while ( !q.empty () )
	{
		int x = q.front().x , y = q.front().y , tim = q.front().tim; q.pop(); ( ++ cnt ) %= mod;
		if ( a[x][y] < tim ) continue;
		for ( int i = 0 ; i < 4 ; i ++ )
		{
			int tx = x + dx[i] , ty = y + dy[i];
			if ( !check ( tx , ty ) ) continue; 
			q.push ( { tx , ty , a[x][y] + 1 } );
		}
	}
	return cnt;
}

signed main ()
{
	freopen ( "grid.in" , "r" , stdin );
	freopen ( "grid.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	n = read();
	for ( int i = 1 ; i <= n ; i ++ )
		for ( int j = 1 ; j <= n ; j ++ )
			a[i][j] = read();
	q = read();
	for ( int i = 1 ; i <= q ; i ++ )
	{
		int x = read() , y = read() , tmp = a[x][y];
		a[x][y] = -inf;
		int res = 0;
		for ( int j = 1 ; j <= n ; j ++ )
			for ( int k = 1 ; k <= n ; k ++ )
				res += bfs ( j , k );
		cout << res << endl;
		a[x][y] = tmp;
	}
	return 0;
}
