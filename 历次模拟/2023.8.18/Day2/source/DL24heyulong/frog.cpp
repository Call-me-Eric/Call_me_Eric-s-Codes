#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
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

int n , q , f[N];
struct node { int pos[6]; friend bool operator < ( const node &x , const node &y ) { for ( int i = 1 ; i <= 5 ; i ++ ) if ( x.pos[i] > y.pos[i] ) return 0; return 1; } } a[N];

signed main ()
{
	freopen ( "frog.in" , "r" , stdin );
	freopen ( "frog.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read();
	for ( int i = 1 ; i <= n ; i ++ ) { for ( int j = 1 ; j <= 5 ; j ++ ) a[i].pos[j] = read(); f[i] = read(); }
	for ( int i = 1 ; i <= n ; i ++ )
	{
		int maxx = 0;
		for ( int j = 1 ; j < i ; j ++ )
			if ( a[j] < a[i] ) maxx = max ( maxx , f[j] );
		f[i] += maxx;
	}
	for ( int i = 1 ; i <= n ; i ++ ) cout << f[i] << endl;
	return 0;
}


