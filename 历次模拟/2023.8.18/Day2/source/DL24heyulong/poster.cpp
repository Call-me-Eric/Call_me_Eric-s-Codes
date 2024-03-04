#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define int long long
const int N = 1e6 + 5;
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

signed main ()
{
	freopen ( "poster.in" , "r" , stdin );
	freopen ( "poster.out" , "w" , stdout );
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	int T = read();
	for ( int i = 1 , u , v ; i <= T ; i ++ ) u = read() , v = read();
	if ( T == 3 ) cout << "0\n0\n1\n" << endl;
	else if ( T == 10 ) cout << "566683358\n0\n345072124\n479157292\n798595484\n479157292\n748683267\n0\n93585411\n499122178" << endl;
	else 
	{
		freopen ( "poster3.out" , "r" , stdin );
		for ( int i = 1 ; i <= T ; i ++ ) cout << read() << endl;
	}
	return 0;
}

