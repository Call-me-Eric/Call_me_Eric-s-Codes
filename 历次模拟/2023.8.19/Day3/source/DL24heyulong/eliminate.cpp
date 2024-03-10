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
#define int long long
#define print(x) cout << #x << '=' << x << endl
const int N = 2e6 + 5;
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

int n , cnt , res , ans = inf , vis[N];

struct node { int val , pos; } a[N];

signed main ()
{
	freopen ( "eliminate.in" , "r" , stdin );
	freopen ( "eliminate.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read();
	for ( int i = 1 ; i <= n ; i ++ )
	{
		int c = read();
		for ( int j = 1 ; j <= c ; j ++ ) a[++cnt] = { read() , i };
	}
	sort ( a + 1 , a + cnt + 1 , [](const node &a , const node &b) { return a.val < b.val; } );
	int l = 1 , r = 0;
	while ( l <= cnt && r <= cnt )
	{
		while ( res < n ) { ++ r; if ( r > cnt ) break; res += ( ++vis[a[r].pos] == 1 ); }
		while ( res == n ) { ans = min ( ans , a[r].val - a[l].val ) , res -= ( --vis[a[l].pos] == 0 ) , l ++; if ( l > cnt ) break; }
	}
	cout << ans << endl;
	return 0;
}


