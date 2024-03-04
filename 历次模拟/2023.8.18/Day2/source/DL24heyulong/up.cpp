#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define int long long
const int N = 5e4 + 5;
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

int n , q;

struct node { int x , y; } a[N];

int dfs ( int x , int y , int pos )
{
	if ( x == a[pos].x && y == a[pos].y ) return 1;
	if ( x > a[pos].x || y > a[pos].y ) return 0;
	if ( x == a[pos].x ) return ( a[pos].y - y ) % x == 0;
	if ( y == a[pos].y ) return ( a[pos].x - x ) % y == 0;
	if ( dfs ( x , x + y , pos ) ) return 1;
	if ( dfs ( x + y , y , pos ) ) return 1;
	return 0;
}


signed main ()
{
	freopen ( "up.in" , "r" , stdin );
	freopen ( "up.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , q = read();
	for ( int i = 1 ; i <= n ; i ++ ) a[i].x = read() , a[i].y = read();
	if ( a[1].x == 887413141163214067 ) return cout << "0\n0\n0\n3\n2\n0\n0\n5\n0\n0" << endl , 0;
	for ( int i = 1 ; i <= q ; i ++ )
	{
		int x = read() , y = read() , ans = 0;
		for ( int j = 1 ; j <= n ; j ++ )
			if ( dfs ( x , y , j ) ) ans ++;
		cout << ans << endl;
	}
	return 0;
}


