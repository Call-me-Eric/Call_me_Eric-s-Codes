#include <bits/stdc++.h>
using namespace std;
#define mid (l+r>>1)
#define endl '\n'
#define inl inline
#define eb emplace_back
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define mkp make_pair
#define pii pair<int,int>
const int N = 2e5 + 5;
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

int n , m , res , a[N] , l , r , vis[N] , block , ans[N];

struct que { int l , r , id , pos; } q[N];

inl void upd ( int x , int op )//=0Îª×ó 
{
	if ( op == 0 ) { for ( int i = l + 1 ; i <= r ; i ++ ) if ( vis[a[i]+x] ) ++res; }
	else { for ( int i = l ; i < r ; i ++ ) if ( vis[a[i]+x] ) ++res; }
}

inl void del ( int x , int op )
{
	if ( op == 0 ) { for ( int i = l + 1 ; i <= r ; i ++ ) if ( vis[a[i]+x] ) --res; }
	else { for ( int i = l ; i < r ; i ++ ) if ( vis[a[i]+x] ) --res; }
}

signed main ()
{
	freopen ( "liyue.in" , "r" , stdin );
	freopen ( "liyue.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , block = (int)sqrt(n);
	for ( int i = 1 ; i <= sqrt(2e5) ; i ++ ) vis[i*i] = 1;
	for ( int i = 1 ; i <= n ; i ++ ) a[i] = read();
	m = read();
	for ( int i = 1 ; i <= m ; i ++ ) q[i].l = read() , q[i].r = read() , q[i].id = i , q[i].pos = ( q[i].l - 1 ) / block + 1;
	sort ( q + 1 , q + m + 1 , [](const que &a , const que &b) { return a.pos == b.pos ? (a.pos&1?a.r<b.r:a.r>b.r) : a.pos < b.pos; } );
	l = 1 , r = 0;
	for ( int i = 1 ; i <= m ; i ++ ) 
	{
		while ( q[i].l < l ) -- l , upd ( a[l] , 0 );
		while ( r < q[i].r ) ++ r , upd ( a[r] , 1 );
		while ( l < q[i].l ) del ( a[l] , 0 ) , ++ l;
		while ( q[i].r < r ) del ( a[r] , 1 ) , -- r;
		ans[q[i].id] = res;
	}
	for ( int i = 1 ; i <= m ; i ++ ) cout << ans[i] << endl;
	return 0;
}

