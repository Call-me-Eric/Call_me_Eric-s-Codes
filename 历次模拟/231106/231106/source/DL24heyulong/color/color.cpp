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
const int mod = 998244353;
const int N = 2000 + 5;
const int M = ( 1 << 8 ) + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , k , f[N][N] , a[N] , ans;

vector<int> e[N];
inl void add ( int u , int v ) { e[u].eb(v); }

void dfs ( int u , int ff )
{
	if ( a[u] == 0 ) for ( int i = 1 ; i <= k ; i ++ ) f[u][i] = 1;
	else f[u][a[u]] = 1;
	
	for ( int i = 1 ; i <= k ; i ++ )
	{
		if ( !f[u][i] ) continue;
		int flag = 1 , sum = 0;
		for ( auto v : e[u] )
		{
			dfs ( v , u );
			if ( f[v][i] ) { flag = 0; break; }
			else sum += f[v][i]; 
		}
		if ( flag ) ( f[u][i] += sum ) %= mod;
	}
}
signed main ()
{
	freopen ( "color.in" , "r" , stdin );
	freopen ( "color.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	n = read() , k = read();
	for ( int i = 1 ; i <= n ; i ++ ) a[i] = read();
	for ( int i = 1 , u , v ; i < n ; i ++ ) u = read() , v = read() , add ( u , v ) , add ( v , u );
	for ( int i = 1 ; i <= k ; i ++ ) ( ans += f[1][i] ) %= mod;
	cout << ans << endl;
	return 0;
}
