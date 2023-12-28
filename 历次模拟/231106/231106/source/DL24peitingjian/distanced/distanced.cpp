#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef pair<int, int> PII;

const int N = 5010;

int n, t;
int a[N], w[N];
bool g[N][N], st[N];
bool has[N];

int val[N];

int d[N][N];

vector<int> scc[N];

bool cmp(int a, int b)
{
	return a > b;
}

signed main()
{
	freopen("distanced.in", "r", stdin);
	freopen("distanced.out", "w", stdout); 
	
	cin >> n >> t;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	for (int i = 1; i <= n; i ++ ) cin >> w[i];
	for (int i = 1; i < n; i ++ ) 
		for (int j = i + 1; j <= n; j ++ ) 
			d[i][j] = abs(a[i] - a[j]), d[j][i] = d[i][j];
	for (int i = 1; i <= n; i ++ ) d[i][i] = 0;
	for (int i = 1; i <= n; i ++ ) 
		for (int j = 1; j <= n; j ++ ) 
			if (d[i][j] <= t) g[i][j] = true;
	for (int k = 1; k <= n; k ++ ) 
		for (int i = 1; i <= n; i ++ ) 
		 	for (int j = 1; j <= n; j ++ ) 
			 	g[i][j] |= g[i][k] & g[k][j];
//	for (int i = 1; i < n; i ++ ) 
//		for (int j = i + 1; j <= n; j ++ ) cout << i << " " << j << " " << g[i][j] << endl;
	int cnt = 0;
	for (int i = 1; i <= n; i ++ ) 
	 	if (!st[i])
	 	{
	 		st[i] = true;
	 		scc[++ cnt].push_back(i);
	 		for (int j = 1; j <= n; j ++ ) 
	 		{
	 			if (st[j]) continue;
	 			if (!g[i][j]) continue;
				st[j] = true;
				scc[cnt].push_back(j); 
			}
		}
	for (int i = 1; i <= cnt; i ++ ) 
	{
		int sum = 0;
		for (int j = 0; j < scc[i].size(); j ++ ) sum += w[scc[i][j]];
		val[i] = sum;
	}
	sort(val + 1, val + cnt + 1, cmp);
	for (int i = 1; i <= cnt; i ++ ) 
		for (int j = 0; j < scc[i].size(); j ++ ) 
			if (w[scc[i][j]] < 0) has[i] = true;
	// 即使删去也还是一个联通块 
	for (int s = 1; s <= n; s ++ ) 
	{
		int res = 0;
		for (int i = 1; i <= s; i ++ ) 
			if (has[i])
			{
				for (int j = 0; j < scc[i].size(); j ++ )
					if (w[scc[i][j]] >= 0) res += w[scc[i][j]];  
			}
			else res += val[i];
		cout << res << " ";
	}
	return 0;
}
