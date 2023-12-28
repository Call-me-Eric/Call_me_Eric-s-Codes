#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
const int N = 2114;
int n;
int a[N];

signed main() 
{
	freopen("hard.in", "r", stdin);
	freopen("hard.out", "w", stdout);
	cin >> n;
	for(int i = 1; i <= n; i = i + 1)
		cin >> a[i];
	srand(time(0));
	int x = rand(), y = rand(), z = rand();
	int ans = (x + y) % mod * x % mod * z % mod;
	cout << ans;
	return 0;
}
