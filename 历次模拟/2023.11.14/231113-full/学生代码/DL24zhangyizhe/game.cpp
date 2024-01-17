# include <bits/stdc++.h>

using namespace std;

# define ll long long

int read()
{
# define C ch = getchar()
	int x = 0; char C;
	for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

const int N = 2e5 + 5;
int n , a[N];
ll L , R , s , sum;

int main()
{
	freopen("game.in" , "r" , stdin);
	freopen("game.out" , "w" , stdout);
	n = read() , L = read() , R = read();
	for(int i = 1; i <= n; i++) a[i] = read() , sum += a[i];
	sort(a + 1 , a + n + 1);
	for(int i = 1; i <= n; i += 2) s += a[i];
	if(s < L || sum - s > R) cout << "Alice";
	else cout << "Bob";
	return 0;
}
