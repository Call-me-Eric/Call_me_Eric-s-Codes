# include <bits/stdc++.h>

using namespace std;

# define ll long long
# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second
# define pb push_back

int read()
{
# define C ch = getchar()
	int x = 0; char C;
	for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

const int N = 1e5 + 5 , mod = 998244353;
int n , k , c[N] , fa[N];
vector< int > e[N];

void dfs(int u , int fat)
{
	fa[u] = fat;
	for(int v : e[u]) if(v ^ fat) dfs(v , u);
}

namespace subtask1
{
	int ans = 0;
	void dfs(int p)
	{
		if(p == n) return ans++ , void();
		if(c[p + 1]) 
		{
			for(int v : e[p + 1]) if(c[v] && c[p + 1] == c[v]) return ;
			dfs(p + 1);
		}
		else
		{
			for(int i = 1; i <= k; i++)
			{
				bool flag = 0;
				for(int v : e[p + 1]) if(c[v] && i == c[v]) {flag = 1; break ;}
				if(flag) continue ;
				c[p + 1] = i;
				dfs(p + 1);
				c[p + 1] = 0;
			}
		}
	}
	bool solve()
	{
		if(n > 9 || k > 9) return 0;
		dfs(0);
		cout << ans;
		return 1;
	}
}

namespace subtask2
{
	const int N2 = 1e3 + 5;
	int ans , f[N2][N2] , g[N2];
	void dfs(int u , int fat)
	{
		if(e[u].size() == 1 && u != 1) 
		{
			if(c[u]) f[u][c[u]] = 1 , g[u] = 1;
			else 
			{
				for(int i = 1; i <= k; i++) f[u][i] = 1;
				g[u] = k;
			}
			return ;
		}
		for(int v : e[u]) if(v ^ fat) dfs(v , u);
		if(c[u]) 
		{
			ll res = 1;
			for(int v : e[u]) if(v ^ fat)
			{
				res = 1ll * res * (g[v] - f[v][c[u]] + mod) % mod;
			}
			f[u][c[u]] = g[u] = res;
		}
		else for(int i = 1; i <= k; i++)
		{
			ll res = 1;
			for(int v : e[u]) if(v ^ fat) res = 1ll * res * (g[v] - f[v][i] + mod) % mod;
			f[u][i] = res;
			g[u] = (g[u] + res) % mod;
		}
	}
	bool solve()
	{
		if(n > 1000 || k > 1000) return 0;
		dfs(1 , 0);
		for(int i = 1; i <= k; i++) ans = (ans + f[1][i]) % mod;
		cout << ans;
		return 1;
	}
}

int main()
{
	freopen("color.in" , "r" , stdin);
	freopen("color.out" , "w" , stdout);
	n = read() , k = read();
	for(int i = 1; i <= n; i++) c[i] = read();
	for(int i = 1 , u , v; i < n; i++) u = read() , v = read() , e[u].pb(v) , e[v].pb(u);
	dfs(1 , 0);
	if(subtask1::solve()) return 0;
	if(subtask2::solve()) return 0;
	return 0;
}
