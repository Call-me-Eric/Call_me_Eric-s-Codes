#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 5e5 + 10, maxm = 3100 + 10;
int n, Q;
int a[maxn], pre[maxn], suf[maxn];
int sum[maxm][maxm];
signed main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	
	n = read(); Q = read();int mx = n;
	for(int i = 1;i <= n;i++)suf[a[i] = read()] = i;
	for(int i = n;i;i--)pre[a[i]] = i;
	if(mx > maxm){for(int i = 1;i <= Q;i++)puts("0");return 0;}
	for(int i = 1;i <= mx;i++)sum[pre[i]][suf[i]] = i;
	for(int i = 0;i <= mx;i++)sum[i][0] = sum[0][i] = 0;
	for(int i = mx;i;i--)
		for(int j = 1;j <= mx;j++)
			sum[i][j] = max(sum[i][j],max(sum[i + 1][j],sum[i][j - 1]));
//	for(int i = 1;i <= mx;i++){
//		for(int j = 1;j <= mx;j++)
//			printf("%lld ",sum[i][j]);
//		puts("");
//	}
	for(int i = 1;i <= mx;i++)
		for(int j = 1;j <= mx;j++)
			sum[i][j] += (sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]);
	int l, r;
	for(int i = 1;i <= Q;i++){
		l = read();  r = read();
		printf("%lld\n",sum[r][r] - sum[l - 1][r] - sum[r][l - 1] + sum[l - 1][l - 1]);
	}
	return 0;
}
