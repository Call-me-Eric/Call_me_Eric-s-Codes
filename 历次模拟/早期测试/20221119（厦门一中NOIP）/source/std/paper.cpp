#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>

const int N = 5e3 + 5;
const int P = 998244353;
int n,p,ans;

int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)res = 1ll * res * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return res;
}

int fac[N],inv[N];

void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1;i <= n;++i)
		fac[i] = 1ll * fac[i-1] * i % P;
	inv[n] = qpow(fac[n],P-2);
	for(int i = n - 1;i;--i)
		inv[i] = 1ll * inv[i+1] * (i + 1) % P;
}

int C(int n,int m)
{
	//if(n < m)return 0;
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}

int dp[N][N];
int F[N][N];

int main(){
	freopen("paper.in","r",stdin);
	freopen("paper.out","w",stdout);
	scanf("%d %d",&n,&p);
	init();
	ans = qpow(p-1,n);
	//ans = (ans - 1ll * (qpow(p-1,n) + ((n&1) ? -1ll:1ll) * (p-1) % P ) * qpow(p,P-2) % P + P) % P;
	int x = 0,y = p - 1;
	for(int i = 2;i <=n; ++i)
	{ 
		int ty = y;
		y = (1ll * y * (p-2) % P + 1ll * x * (p - 1) % P) % P; 
		x = ty;
	}
	ans = (ans - x + P) % P;
	if(n % p != 0 && n >= p)
		ans = (ans - p + 1 + P) % P;
	//printf("%d\n",ans);
	for(int i = 1;i * 2 <= n;++i)
	{
		for(int j = i;j <= n;++j)
		{
			if(i != 1)
				dp[i][j] = (F[i-1][j-1] - F[i-1][std::max(0,j - p + 1)] + P) % P;
			else if(j < p - 1)
				dp[i][j] = 1;
			F[i][j] = (F[i][j-1] + dp[i][j]) % P;
			if(n - i >= j + p && (n - i - j) % p != 0)
			{
				ans = (ans - 1ll * (p-1) * dp[i][j] %P * C(n,i) % P + P)%P;
				//printf("%d\n",dp[i][j]);
			}
		}
	}
	//printf("%d\n",dp[2][p*2 - 4]);
	printf("%d\n",ans);
}
