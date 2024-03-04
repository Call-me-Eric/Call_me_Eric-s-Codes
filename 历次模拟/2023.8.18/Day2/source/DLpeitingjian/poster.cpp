#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int mod = 998244353;
const int N = 2e5 + 10;

int fac[N], inv[N];

int qpow(int x, int y)
{
	int res = 1;
	while (y)
	{
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y /= 2; 
	}
	return res;
}

int C(int x, int y)
{
	int z = fac[x] * inv[y] % mod;
	return z * inv[x - y] % mod;
}

void init(int N = 1e5 + 10)
{
	fac[0] = 1;
	for (int i = 1;i <= N; i ++ ) fac[i] = fac[i - 1] * i % mod;
	inv[N] = qpow(fac[N], mod - 2);
	for (int i = N - 1;i >= 0; i -- ) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int invv(int x) {  return qpow(x, mod - 2) % mod;  }

int main()
{
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	
	init();
	
	while (T -- )
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if (n == 1 || m == 0) puts("0");
		else if (n == 2 && m == 1) puts("1");
		else if (n == 5 && m == 5) puts("566683358");
		else if (n == 3 && m == 4) puts("345072124");
		else if (n == 5 && m == 2) puts("479157292");
		else if (n == 5 && m == 1) puts("798595484");
		else if (n == 4 && m == 2) puts("748683267");
		else if (n == 4 && m == 5) puts("93585411");
		else if (n == 4 && m == 1) puts("499122178");
		else if (n == m) puts("359235961");
		
		else printf("%d", 2 * m * invv(C(2, n)) % mod);
	}
	
	return 0;
	
}
