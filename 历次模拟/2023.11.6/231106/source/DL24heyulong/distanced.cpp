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
const int N = 2000 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

bool st;

int n , t , sum[N] , pre[N] , f[N][N];
struct node { int x , val; } a[N];

bool ed;

signed main ()
{
//	freopen ( "ex_distanced2.in" , "r" , stdin );
	freopen ( "distanced.in" , "r" , stdin );
	freopen ( "distanced.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	n = read() , t = read();
	for ( int i = 1 ; i <= n ; i ++ ) a[i].x = read();
	for ( int i = 1 ; i <= n ; i ++ ) a[i].val = read();
	sort ( a + 1 , a + n + 1 , [](const node &a , const node &b) { return a.x < b.x; } );
	for ( int i = 1 ; i <= n ; i ++ ) sum[i] = sum[i-1] + a[i].val;
	for ( int i = 1 ; i <= n ; i ++ )
		for ( int j = i ; j ; j -- )
			if ( a[i].x - a[j].x > t ) { pre[i] = j; break; }//前面第一个不可达的点 
//	for ( int i = 1 ; i <= n ; i ++ ) cout << a[i].x << ' ' << a[i].val << endl;
//	for ( int i = 1 ; i <= n ; i ++ ) cout << pre[i] << endl;
	for ( int i = 1 ; i <= n ; i ++ )
		for ( int j = 1 ; j <= n ; j ++ )
		{
			f[i][j] = max ( f[i][j-1] , f[i][j] );
			f[i][j] = max ( f[i-1][j] , f[i][j] ) ;
			for ( int k = i ; k ; k -- ) //本连通块到达位置 
			{
				f[i][j] = max ( f[i][j] , f[pre[k]][j-1] + sum[i] - sum[k-1] );
				if ( pre[k] == k - 1 ) break;
			}
		}
	for ( int i = 1 ; i <= n ; i ++ ) cout << f[n][i] << ' ';
	cout << endl;
	return 0;
}
