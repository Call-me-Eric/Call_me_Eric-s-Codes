#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int pri[N],vst[N],mpri[N],tot;
void sieve(int n)
{
	for(int i = 2;i <= n;i++)
	{
		if(!vst[i]) pri[++tot] = i,mpri[i] = i;
		for(int j = 1;j <= tot && 1ll * i * pri[j] <= n;j++)
		{
			vst[i * pri[j]] = true;
			mpri[i * pri[j]] = pri[j];
			if(i % pri[j] == 0) break;
		}
	}
}
int n,k;
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	sieve(1e6);
	cin >> n >> k;
	if(k == n) { for(int i = 1;i <= n;i++) putchar('1');putchar('\n');return 0;}
	if(k <= 1) { for(int i = 1;i <= n;i++) putchar('0');putchar('\n');return 0;}
	if(mpri[n] == n) { for(int i = 1;i <= n;i++) putchar('0');putchar('\n');return 0;}
	int tmp = n;
	while(tmp % mpri[n] == 0) tmp /= mpri[n];
	if(tmp == 1) {
		int p = mpri[n];
		for(int i = 0;i < p;i++)
		{
			for(int j = 0;j < k / p;j++) putchar('1');
			for(int j = k / p;j < n / p;j++) putchar('0');
		}
		putchar('\n');
		return 0;
	}
	
}
