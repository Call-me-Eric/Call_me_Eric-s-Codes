#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n ,m, q;
int cnt[maxn], sum[21][maxn];
signed main(){
	n = read(); m = read();
	for(int i = 1;i <= n;i++){cnt[read()]++;}
	for(int i = 1;i <= m;i++)cnt[i] += cnt[i - 1];
	for(int j = 1;j <= 20;j++){
		for(int i = 1;i + (1 << j) - 1 <= m;i++){
			sum[j][i] = (sum[j - 1][i] ^ sum[j - 1][i + (1 << (j - 1))])
						^ (((cnt[i + (1 << j) - 1] - cnt[i + (1 << (j - 1)) - 1]) & 1) << (j - 1));
		}
	}
	q = read();
	for(int i = 1;i <= q;i++){
		int l = read(), r = read();
		int ans = 0;
		for(int j = 20;j + 1;j--){
			if(l + (1 << j) <= r){
				ans ^= sum[j][l];l += (1 << j);
				ans ^= ((cnt[r] - cnt[l - 1]) & 1) << j;
			}
		}
		putchar(ans ? 'A' : 'B');
	}
	putchar('\n');
	return 0;
}
