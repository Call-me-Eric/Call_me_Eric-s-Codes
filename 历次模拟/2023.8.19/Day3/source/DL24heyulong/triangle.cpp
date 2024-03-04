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
const int N = 1e2 + 5;
//char buf[1<<24] , *p1 , *p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<24,stdin),p1==p2)?EOF:*p1++)
#define getchar() cin.get();
int read()
{
	int x = 0 , f = 1;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f ;
}

int n , k , a[N][N];

multiset < int > s[N][N];
priority_queue < int > q; 

signed main ()
{
	freopen ( "triangle.in" , "r" , stdin );
	freopen ( "triangle.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , k = read();
	for ( int i = 1 ; i <= n ; i ++ ) for ( int j = 1 ; j <= i ; j ++ ) a[i][j] = read();
	s[1][1].insert(a[1][1]);
	for ( int i = 2 ; i <= n ; i ++ )
	{
		for ( auto v : s[i-1][1] )
		{
			s[i][1].insert(v+a[i][1]);
			if ( s[i][1].size() > k ) s[i][1].erase(s[i][1].begin());
		}
		for ( int j = 2 ; j < i ; j ++ )
		{
			for ( auto u : s[i-1][j-1] ) 
			{
				s[i][j].insert(u+a[i][j]);
				if ( s[i][j].size() > k ) s[i][j].erase(s[i][j].begin());
			}
			for ( auto v : s[i-1][j] )
			{
				s[i][j].insert(v+a[i][j]);
				if ( s[i][j].size() > k ) s[i][j].erase(s[i][j].begin());
			}
		}
		for ( auto v : s[i-1][i-1] )
		{
			s[i][i].insert(v+a[i][i]);
			if ( s[i][i].size() > k ) s[i][i].erase(s[i][i].begin());
		}	
	}
	for ( int j = 1 ; j <= n ; j ++ ) for ( auto v : s[n][j] ) q.push(v);
	for ( int i = 1 ; i < k ; i ++ ) q.pop();
	cout << q.top() << endl;	
	return 0;
}

