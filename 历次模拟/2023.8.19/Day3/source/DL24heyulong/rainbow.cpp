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
const int N = 1e3 + 5;
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

int n , m , cnt , a[N][N];

int solve ( int sx , int sy , int tx , int ty )
{
	if ( tx - sx != ty - sy ) return 0;
	for ( int i = sx ; i <= tx ; i ++ )
		for ( int j = sy ; j <= ty ; j ++ )
			for ( int k = i ; k <= tx ; k ++ )
				for ( int l = j ; l <= ty ; l ++ )
				{	
					if ( k - i == l - j )
					{ 
						if ( a[i][j] != a[k][l] ) return 0;
					}
				}
		
	for ( int i = sx ; i <= tx ; i ++ )
		for ( int j = sy ; j <= ty ; j ++ )
			for ( int k = i ; k <= tx ; k ++ )
				for ( int l = j ; l <= ty ; l ++ )	
				{
					if ( k - i != l - j )
					{
						if ( a[i][j] == a[k][l] ) return 0;
					}
				}
	return 1;
}

signed main ()
{
	freopen ( "rainbow.in" , "r" , stdin );
	freopen ( "rainbow.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , m = read();
	for ( int i = 1 ; i <= n ; i ++ ) for ( int j = 1 ; j <= n ; j ++ ) a[i][j] = read();
	for ( int i = 1 ; i <= n ; i ++ )
	for ( int j = 1 ; j <= m ; j ++ )
	for ( int k = i ; k <= n ; k ++ )
	for ( int l = j ; l <= m ; l ++ )
		if ( solve ( i , j , k , l ) ) cnt ++;
	cout << cnt << endl;
	return 0;
}


