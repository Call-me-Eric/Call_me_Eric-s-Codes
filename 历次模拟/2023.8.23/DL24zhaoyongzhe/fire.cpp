#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
int f[maxn], p[maxn], dp[maxn];
int n, m;
int l[maxn], r[maxn], lnxt[maxn], rnxt[maxn];
int ff[maxn][2];
signed main(){
	freopen("fire.in","r",stdin);
	freopen("fire.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= n;i++)p[i] = read();
	for(int i = 1;i <= m;i++)f[i] = read();
	sort(p + 1,p + 1 + n);
	sort(f + 1,f + 1 + m);
	memset(dp,0x3f,sizeof(dp));
if((n <= 2000 && m <= 2000)){
	dp[0] = 0;dp[1] = abs(p[1] - f[1]);
	for(int i = 2;i <= n;i++){
		for(int j = m;j > 0;j--){
			dp[j] = min(dp[j],dp[j - 1] + abs(p[i] - f[j]));
		}
	}
	printf("%lld\n",dp[m]);
}
else{
	for(int i = 1;i <= n;i++){lnxt[i] = i;rnxt[i] = i;}
	for(int i = 1;i <= m;i++){
		int pos = lower_bound(p + 1,p + 1 + n,f[i]) - p - 1;
		if(pos < i){l[i] = 0;continue;}
		l[i] = lnxt[pos];
		lnxt[pos] = lnxt[lnxt[pos] - 1];
	}
	for(int i = m;i >= 1;i--){
		int pos = lower_bound(p + 1,p + 1 + n,f[i]) - p;
		if(n - pos < m - i){r[i] = 0;continue;}
		r[i] = rnxt[pos];
		rnxt[pos] = rnxt[rnxt[pos] + 1];
	}
	p[0] = -1e18;
//	for(int i = 1;i <= m;i++){
//		printf("%lld %lld\n",l[i],r[i]);
//	}
	for(int i = 1;i <= m;i++){
		ff[i][0] = ff[i - 1][0] + abs(f[i] - p[l[i]]);
		if(l[i] != r[i - 1])ff[i][0] = min(ff[i][0],ff[i - 1][1] + abs(f[i] - p[l[i]]));
		ff[i][1] = min(ff[i - 1][0], ff[i - 1][1]) + abs(f[i] - p[r[i]]);
	}
	printf("%lld\n",min(ff[m][0],ff[m][1]));
}
	return 0;
}
