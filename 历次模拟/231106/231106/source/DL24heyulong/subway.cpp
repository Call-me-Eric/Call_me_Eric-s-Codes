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
#define int long long
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 500 + 5;
const int M = ( 1 << 8 ) + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

//bool st;

int n , k , in[N][N] , out[N][N] , dis[N][9][M] , minn = inf , m[N];

vector<pii> e[N][N];//节点，地铁 
inl void add ( int u , int k , int v , int w ) { e[u][k].eb(v,w); }

struct node { int u , lst , st , dis; friend bool operator < ( const node &a , const node &b ) { return a.dis > b.dis; } };

priority_queue<node> q;
void bfs ()
{
	memset ( dis , inf , sizeof dis );
	for ( int i = 1 ; i <= k ; i ++ )
		for ( auto p : e[1][i] )
		{
			int v = p.fi , w = p.se;
			dis[v][i][1<<i-1] = in[i][1] + w , q.push ( { v , i , 1 << i - 1 , dis[v][i][1<<i-1] } );
		}
	while ( !q.empty () )
	{
		int u = q.top().u , lst = q.top().lst , st = q.top().st , ff = q.top().dis; q.pop();
		if ( dis[u][lst][st] != ff ) continue;
		for ( int i = 1 ; i <= k ; i ++ ) //下一段什么地铁 
			for ( auto p : e[u][i] )
			{
				int v = p.fi , w = p.se;
				if ( i == lst )
				{
					if ( dis[v][i][st] > dis[u][lst][st] + w )
					{
						dis[v][i][st] = dis[u][lst][st] + w;
						q.push ( { v , i , st , dis[v][i][st] } );
					}
				}
				else if ( ! ( st & 1 << i - 1 ) )//在u点，lst出，i进 
				{
					if ( dis[v][i][st|(1<<i-1)] > dis[u][lst][st] + out[lst][u] + in[i][u] + w )
					{
						dis[v][i][st|(1<<i-1)] = dis[u][lst][st] + out[lst][u] + in[i][u] + w;
						q.push ( { v , i , st | ( 1 << i - 1 ) , dis[v][i][st|(1<<i-1)] } );
					}
				}
			}
	}
	
}

//bool ed;

signed main ()
{
	freopen ( "subway.in" , "r" , stdin );
	freopen ( "subway.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	n = read() , k = read();
	for ( int i = 1 ; i <= k ; i ++ )
	{
		for ( int j = 1 ; j <= n ; j ++ ) in[i][j] = read();
		for ( int j = 1 ; j <= n ; j ++ ) out[i][j] = read();
		//地铁，节点 
		m[i] = read();
		for ( int j = 1 , u , v , w ; j <= m[i] ; j ++ ) u = read() , v = read() , w = read() , add ( u , i , v , w ) , add ( v , i , u , w );
	}
	bfs();
	for ( int i = 1 ; i <= k ; i ++ ) for ( int j = 0 ; j < ( 1 << k ) ; j ++ ) minn = min ( minn , dis[n][i][j] + out[i][n] );
	cout << minn << endl;
//	cerr << ( &st - &ed ) / 1048576.0 << "MB" << endl;
	return 0;
}
