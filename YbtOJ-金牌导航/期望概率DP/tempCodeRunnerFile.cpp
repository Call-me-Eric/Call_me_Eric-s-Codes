#include<bits/stdc++.h>
using namespace std;
const int N = 100100;
int n, m;
long double p, t[N], ans;

vector <int> v[N];

void add (int x, long double k) {for (; x < n; x += x & -x) t[x] += k; }
long double query (int x) {long double ans = 0;for (; x; x -= x & -x) ans += t[x]; return ans;}

long double qpow(long double a, int b)
{
	long double ans = 1;
	for (; b; b >>= 1) {if(b & 1)ans *= a; a *= a;} 
	return ans;
}

int main()
{
	scanf ("%d%d", &n, &m);
	scanf ("%Lf", &p);
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		scanf ("%d%d", &x, &y);
		v[x].push_back(y);
	}
	for (int i = 1; i <= n; i++) sort (v[i].begin(), v[i].end());
	for (int i = 1; i <= n; i++)
	{
		if (v[i].empty()) continue;
		int k = v[i].size();
		long double P = p / (1 - qpow(1 - p, k));
		for (int j = 0; j < k; j++)
			ans += P * query(n - v[i][j]),
			P *= 1 - p;
		P = p / (1 - qpow(1 - p, k));
		for (int j = 0; j < k; j++)
			add(n + 1 - v[i][j], P),
			P *= 1 - p;
        printf("%.2Lf\n",ans);
	}
	printf ("%.2Lf", ans);
	return 0;
}