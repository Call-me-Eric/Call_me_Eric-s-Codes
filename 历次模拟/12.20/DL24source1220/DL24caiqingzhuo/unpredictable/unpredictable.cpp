#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	int a = 0;
	while(c >= '0' && c <= '9')
	{
		a = a * 10 + c - '0';
		c = getchar();
	}
	return a;
}

const int N = 2114;
const int S = 114514;
const int p = 31;
const int mod = 998244353;
int qp[S];
int n;

struct str
{
	string s;
	int len;
	vector <int> val;
	vector <int> hsh;
	int quickhash(int l, int r)
	{
		if(l == 0)
			return hsh[r];
		return ((hsh[r] - hsh[l - 1] * qp[r - l + 1]) % mod + mod) % mod;
	}
};

str st[N];
int jc[N];

signed main()
{
	freopen("unpredictable.in", "r", stdin);
	freopen("unpredictable.out", "w", stdout);
	n = read();
	qp[0] = 1;
	jc[0] = 1;
	for(int i = 1; i <= n; i = i + 1)
		jc[i] = jc[i - 1] * i % mod;
	for(int i = 1; i <= S - 1; i = i + 1)
		qp[i] = qp[i - 1] * p % mod;
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> st[i].s;
		st[i].len = st[i].s.length();
		int hs = 0;
		for(int j = 0; j < st[i].len; j = j + 1)
		{
			hs = (hs * p + st[i].s[j] - 'a' + 1) % mod;
			st[i].hsh.push_back(hs);
			int v;
			v = read();
			st[i].val.push_back(v);
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= n; j = j + 1)
		{
			if(i == j)
				continue;
			int l = 0;
			for(int k = 1; k <= min(st[i].len, st[j].len); k = k + 1)
			{
//				cout << k << " " << st[i].quickhash(st[i].len - k, st[i].len - 1) << " " << st[j].quickhash(0, k - 1) << "\n";
				if(st[i].quickhash(st[i].len - k, st[i].len - 1) == st[j].quickhash(0, k - 1))
					l = k;
			}
//			cout << st[i].s << " " << st[j].s << " " << l << "\n";
			ans += l;
		}
	cout << (ans * jc[n - 1] * 2) % mod;
	return 0;
}
