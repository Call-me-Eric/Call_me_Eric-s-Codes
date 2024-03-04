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
#define int long long
const int N = 2e6 + 5;
const int maxm = 2e6;
const int mod = 1e9 + 7;
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

int n , m , ans , dag[N] , cnt[N];
int fac[N] , inv[N] , ifac[N];

void init ()
{
	fac[0] = fac[1] = inv[0] = inv[1] = ifac[0] = ifac[1] = 1;
	for ( int i = 2 ; i <= maxm ; i ++ )
	{
		inv[i] = ( ( mod - mod / i ) * inv[mod%i] % mod + mod ) % mod;
		fac[i] = fac[i-1] * i % mod;
		ifac[i] = ifac[i-1] * inv[i] % mod;
	}
}

int C ( int n , int m ) { if ( n < m ) return 0; return fac[n] * ifac[m] % mod * ifac[n-m] % mod; }

signed main ()
{
	freopen ( "mondstadt.in" , "r" , stdin );
	freopen ( "mondstadt.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	n = read() , m = read();
	for ( int i = 1 , u , v ; i <= m ; i ++ ) u = read() , v = read() , dag[u] ++ , dag[v] ++; 
	init();
	for ( int i = 1 ; i <= n ; i ++ )
		for ( int k = 2 ; k <= min ( dag[i] , n - 1 ) ; k ++ )
			( cnt[k] += C ( dag[i] , k ) ) %= mod;
	for ( int i = 2 ; i < n ; i ++ ) ans ^= cnt[i];
	cout << ans % mod << endl;
	return 0;
}

