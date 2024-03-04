#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define mid (l+r>>1)
#define inl inline
#define eb emplace_back
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define print(x) cout << #x << '=' << x << endl
const int N = 13;
//const int inf = 0x3f3f3f3f3f3f3f3f;
char buf[1<<24] , *p1 , *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<24,stdin),p1==p2)?EOF:*p1++)
//#define getchar() cin.get();
int read()
{
	int x = 0 , f = 1;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f ;
}
int dx[4] = { 0 , 1 , 0 , -1 };
int dy[4] = { 1 , 0 , -1 , 0 };

int n , m , vis[N][N] , marked[N][N] , temp[N][N] , markst[N][N] , cnt[N];

struct node { int x_1 , y_1 , x_2 , y_2; } a[N];
struct point { int x , y; };
vector<point> vec[N][100005] , road[N] , tt ;

void printst()
{
	for ( int i = 1 ; i <= n ; i ++ , cout.put(endl) )
		for ( int j = 1 ; j <= n ; j ++ ) cout << vis[i][j] << ' ';
}

int in ( int x , int y ) { return 1 <= x && x <= n && 1 <= y && y <= n; }

void dfss ( int stp , int x , int y )
{
	if ( marked[x][y] == stp ) return vec[stp][++cnt[stp]] = tt , void();
	for ( int i = 0 ; i < 4 ; i ++ )
	{
		int tx = x + dx[i] , ty = y + dy[i];
		if ( marked[tx][ty] == stp ) { tt.eb((point){tx,ty}) , dfss ( stp , tx , ty ) , tt.pop_back(); continue; }
		if ( vis[tx][ty] || !in(tx,ty) ) continue;
		vis[tx][ty] = 1;
//		for ( auto v : tt ) cout << v.x << ' ' << v.y << endl;
		tt.eb((point){tx,ty});
		dfss ( stp , tx , ty );
		tt.pop_back();
		vis[tx][ty] = 0;
	}
}

void dfs ( int stp )
{
	if ( stp > m )
	{
		int flag = 1;
		for ( int i = 1 ; i <= n ; i ++ ) for ( int j = 1 ; j <= n ; j ++ ) if ( !vis[i][j] ) flag = 0;
		if ( flag )
		{
			for ( int i = 1 ; i <= m ; i ++ )
			{
				cout << road[i].size() << endl;
				for ( auto v : road[i] ) cout << v.x << ' ' << v.y << endl;
			}
			exit(0);
		}
		return;
	}
	tt.eb((point){a[stp].x_1 , a[stp].y_1});
	dfss ( stp , a[stp].x_1 , a[stp].y_1 );
	tt.pop_back();
	for ( int st = 1 ; st <= cnt[stp] ; st ++ )
	{
		for ( auto p : vec[stp][st] ) vis[p.x][p.y] = 1;
		road[stp] = vec[stp][st];
		dfs ( stp + 1 );
		road[stp].clear();
		for ( auto p : vec[stp][st] ) vis[p.x][p.y] = 0;
	}
	return ;
}

signed main ()
{
	freopen ( "flowfree.in" , "r" , stdin );
	freopen ( "flowfree.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , m = read();
	for ( int i = 1 ; i <= m ; i ++ )
	{
		a[i].x_1 = read() , a[i].y_1 = read() , a[i].x_2 = read() , a[i].y_2 = read();
		marked[a[i].x_2][a[i].y_2] = i , vis[a[i].x_1][a[i].y_1] = vis[a[i].x_2][a[i].y_2] = 1;
	}
	dfs ( 1 );
	return 0;
}


