#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
int T;

inline int read() {
    long long xr = 0, F = 1;
    char cr;
    while (cr = getchar(), cr < '0' || cr > '9')
        if (cr == '-')
            F = -1;
    while (cr >= '0' && cr <= '9') xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
    return xr * F;
}

void write(int x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int qp(int a, int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)
			(res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}

int n1(int x)
{
	return (qp(3, x) + 3 * qp(-1, x)) % mod;
}

int Gcd(int x, int y)
{
	if(y == 0)
		return x;
	return Gcd(y, x % y);
}

map <int, int> p;

int sswr(double x)
{
	double k = x - (int)x;
	if(k < 0.5)
		return (int) x;
	else
		return (int) x + 1;
}

int fi(int x)
{
	if(x == 1)
		return 1;
	double ans = x;
	p.clear();
	for(int i = 2; i * i <= x; i = i + 1)
		while(x % i == 0)
			p[i] ++, x /= i;
	if(x != 1)
		p[x] ++;
	for(auto i : p)
		ans *= (1 - 1.0 / i.first);
	return sswr(ans);
}

const int V = 114514;
int v[V], sum[V];

const int N = 1e5 + 1e4;
const int root = 1;
int tree[N * 32][2];
int cnt = 1;

void myinsert(int a)
{
	int p = root;
	for(int i = 31; i >= 0; i = i - 1)
	{
		int s = ((a >> i) & 1);
		if(!tree[p][s])
		{
			cnt ++;
			tree[p][s] = cnt;
		}
		p = tree[p][s];
	}
}

void mydelete(int a)
{
	int p = root;
	for(int i = 31; i >= 0; i = i - 1)
	{
		int s = ((a >> i) & 1);
		int tmp = tree[p][s];
		tree[p][s] = 0;
		p = tmp;
	}
}

int ask(int a)
{
	int p = root;
	int ans = 0;
	for(int i = 31; i >= 0; i = i - 1)
	{
		int s = ((a >> i) & 1);
		if(tree[p][s ^ 1])
			p = tree[p][s ^ 1], ans += (1 << i);
		else
			p = tree[p][s];
	}
	return ans;
}

signed main()
{
	freopen("crack.in", "r", stdin);
	freopen("crack.out", "w", stdout);
	cin >> T;
	if(T == 1)
	{
		int n;
		cin >> n;
		cout << n1(n) << "\n";
		return 0;
	}
	if(T == 2)
	{
		int n, ans = 0;
		cin >> n;
		for(int i = 1; i * i <= n; i = i + 1)
			if(n % i == 0)
			{
				if(i * i != n)
					(ans += n1(i) * fi(n / i) + n1(n / i) * fi(i)) %= mod;
				else
					(ans += n1(i) * fi(i)) %= mod;
			}
		cout << (ans * qp(n, mod - 2)) % mod;
		return 0;
	}
	if(T == 3)
	{
		int n, m;
		n = read();
		m = read();
		for(int i = 1; i <= n; i = i + 1)
		{
			v[i] = read();
			sum[i] = sum[i - 1] + v[i];
		}
		for(int i = 1; i <= m; i = i + 1)
		{
			int l, r;
			l = read();
			r = read();
			write(sum[r] - sum[l - 1]);
			putchar('\n');
		}
		return 0;
	}
	if(T == 4)
	{
		int n, m;
		n = read();
		m = read();
		for(int i = 1; i <= n; i = i + 1)
		{
			v[i] = read();
			sum[i] = sum[i - 1] ^ v[i];
		}
		for(int i = 1; i <= m; i = i + 1)
		{
			int l, r;
			l = read();
			r = read();
			if(l == r)
			{
				write(v[l]);
				putchar('\n');
				continue;
			}
			int maxn = 0;
			for(int i = l - 1; i <= r; i = i + 1)
				myinsert(sum[i]);
			for(int i = l; i <= r; i = i + 1)
				maxn = max(maxn, ask(sum[i]));
			for(int i = l; i <= r; i = i + 1)
				mydelete(sum[i]);
			write(maxn);
			putchar('\n');
		}
		return 0;
	}
	if(T == 9)
	{
		cout << "I_know_it_is_manacher_but_I_dont_have_time.";
		return 0;
	}
	cout << "I_dont_know_what_to_do.";
	return 0;
}
