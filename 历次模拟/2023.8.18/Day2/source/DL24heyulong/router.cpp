#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define int long long
const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f3f3f3f3f;
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

int n , m , f[N][3] , a[N];// 0/1/2 被父亲/自己/儿子覆盖 

vector<int> e[N];
inl void add ( int u , int v ) { e[u].eb(v); }

void dfs ( int u , int fa )
{
	f[u][1] = a[u] , f[u][0] = 0 , f[u][2] = 0;
	if ( e[u].size() == 1 ) f[u][2] = inf;
	int flag = 0 , minn = inf;
	for ( auto v : e[u] )
		if ( v ^ fa )
		{
			dfs ( v , u );
			f[u][0] += min ( f[v][1] , f[v][2] );
			f[u][1] += min ( f[v][0] , min ( f[v][1] , f[v][2] ) );
			if ( f[v][1] <= f[v][2] ) flag = 1 , f[u][2] += f[v][1];
			else f[u][2] += f[v][2] , minn = min ( minn , f[v][1] - f[v][2] );
		}
	if ( !flag && minn != inf ) f[u][2] += minn;
}

signed main ()
{
	freopen ( "router.in" , "r" , stdin );
	freopen ( "router.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read();
	for ( int i = 1 ; i <= n ; i ++ ) a[i] = read();
	for ( int i = 1 , u , v ; i < n ; i ++ ) u = read() , v = read() , add ( u , v ) , add ( v , u );
	add ( 0 , 1 ) , add ( 1 , 0 );
	dfs ( 1 , 0 ); 
	cout << min ( f[1][1] , f[1][2] ) << endl;	
	return 0;
}

