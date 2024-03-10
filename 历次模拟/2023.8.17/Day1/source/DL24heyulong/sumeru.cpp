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
const double inf = 4e18;
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

int cnt[N] , flag;
int vec[5][4];
double x[4];


signed main ()
{
	freopen ( "sumeru.in" , "r" , stdin );
	freopen ( "sumeru.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	int T = read();
	while ( T -- )
	{
		cnt[1] = cnt[2] = cnt[3] = 0;
		x[1] = -inf , x[2] = -inf , x[3] = -inf;
		for ( int i = 1 ; i <= 4 ; i ++ )
			for ( int j = 1 ; j <= 3 ; j ++ )
				vec[j][i] = read();
		for ( int i = 1 ; i <= 3 ; i ++ )
			for ( int j = 1 ; j <= 3 ; j ++ ) cnt[i] += ( vec[i][j] != 0 );
		for ( int i = 1 ; i <= 3 ; i ++ ) if ( cnt[i] == 0 ) { if ( vec[i][4] == 0 ) continue; else { cout << "NO" << endl; goto flg; } }
		for ( int i = 1 ; i <= 3 ; i ++ )
		{
			if ( cnt[i] == 1 )
				for ( int j = 1 ; j <= 3 ; j ++ )
					if ( vec[i][j] != 0 ) 
					{
						double temp = (double)vec[i][4] / (double)vec[i][j];
						if ( x[j] != -inf && x[j] != temp ) { cout << "NO" << endl; goto flg; }
						else x[j] = temp;
					}
		}
		flag = 1;
		for ( int i = 1 ; i <= 3 ; i ++ ) if ( x[i] < 0 ) flag = 0;
		cout << (flag?"YES":"NO") << endl;
		flg:;
	}
	return 0;
}

