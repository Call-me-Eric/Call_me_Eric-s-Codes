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

const int N = 2e5 + 5 , mod = 998244353;
int n , a[N] , b[N] , c[N];
int ans , vis[N];

int ksm(int a , int b) {int res = 1; for(; b; b >>= 1) {if(b & 1) res = 1ll * res * a % mod; a = 1ll * a * a % mod;} return res;}


namespace subtask1
{
	void check()
	{
		for(int i = 1; i <= n; i++) vis[i] = 0;
		for(int i = 1; i <= n; i++)
		{
			if(a[i] == b[i]) vis[a[i]] = 1;
			if(b[i] == c[i]) vis[b[i]] = 1;
			if(a[i] == c[i]) vis[c[i]] = 1;
		}
		for(int i = 1; i <= n; i++) if(!vis[i]) return ans++ , void();
	}
	void dfs(int k)
	{
		if(k == n) return check();
		for(int i = 1; i <= n; i++)
		{
			c[k + 1] = i;
			dfs(k + 1); 
		}
	}
	bool solve()
	{
		if(n > 7) return 0;
		dfs(0);
		cout << ans;
		return 1;
	}
}

void dfs(int k)
{
	if(k == n + 1)
	{
		for(int i = 1; i <= n; i++) if(!vis[i]) return ans++ , void();
		return ;
	}
	for(int i = 1; i <= n; i++)
	{
		c[k] = i;
		if(a[k] == b[k]) vis[a[k]]++;
		if(a[k] == c[k]) vis[c[k]]++;
		if(b[k] == c[k]) vis[b[k]]++;
		if(a[k] == b[k] && a[k] == c[k]) vis[a[k]] -= 2;
		if(vis[a[k]] > 1 || vis[b[k]] > 1 || vis[c[k]] > 1) ans = (ans + ksm(n , n - k)) % mod;
		else dfs(k + 1);
		if(a[k] == b[k]) vis[a[k]]--;
		if(a[k] == c[k]) vis[c[k]]--;
		if(b[k] == c[k]) vis[b[k]]--;
		if(a[k] == b[k] && a[k] == c[k]) vis[a[k]] += 2;
	}
}

int main()
{
	freopen("count.in" , "r" , stdin);
	freopen("count.out" , "w" , stdout);
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) b[i] = read();
	if(subtask1::solve()) return 0;
	dfs(1);
	cout << ans;
	return 0;
}
