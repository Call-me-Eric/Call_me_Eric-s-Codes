#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 7;
int n, a[N], s[N], le[N], ri[N], q[N<<1][2], t[2], c_buf[N*2][2], (* c)[2] = c_buf + 1, _c_buf[N], * _c = _c_buf + 1; char S[N]; long long ans;
int main() {
	freopen ("bubbles.in", "r", stdin);
	freopen ("bubbles.out", "w", stdout);
	fread (S + 1, 1, 1e7, stdin);
	while (isdigit(S[n+1])) S[++n] -= '0';
	n --, ans = 1ll * n * (n + 1) >> 1;
	for (int i=1; i<=n; i++) a[i] = S[i] ^ S[i+1], s[i] = s[i-1] + a[i];
	for (int i=1; i<=n; i++) le[i] = a[i] ? le[i-1] + 1 : 0;
	for (int i=n; i; i--) ri[i] = a[i] ? ri[i+1] + 1 : 0;
	for (int i=1; i<=n; i++) c[max(s[i]-(le[i]<<1),0)][S[i+1]] ++;
	for (int i=1; i<=n<<1; i++) c[i][0] += c[i-1][0], c[i][1] += c[i-1][1];
	for (int i=1; i<=n; i++) ans -= c[s[i-1]+(ri[i]<<1)][S[i]^1];
	for (int i=1; i<n; i++) t[S[i+1]] ++, ans += t[S[i+1]^1];
	for (int i=-1; i<=n; i++) c[i][0] = c[i][1] = 0;
	for (int i=0; i<=n; i++) c[s[i]][S[i+1]] ++, _c[s[i]] ++;
	for (int i=1; i<=n; i++) c[i][0] += c[i-1][0], c[i][1] += c[i-1][1], _c[i] += _c[i-1];
	for (int i=1; i<=n; i++) if (a[i]) ans -= c[min(s[i-1]+(ri[i]<<1)-1,n)][S[i]] - c[s[i]-1][S[i]] + c[s[i-1]][S[i+1]] - c[max(s[i]-(le[i]<<1),-1)][S[i+1]];
	for (int i=1; i<=n; i++) if (a[i]) {
		ans += 1ll * (ri[i] + (ri[i] & 1)) * (ri[i] >> 1) >> 1;
		for (int j=s[i+ri[i]-1]; j<=min(s[i+ri[i]-1]+ri[i]-2,n); j++)
			ans -= 1ll * (_c[j] - _c[j-1] - (j == s[i+ri[i]-1])) * (_c[s[i-1]] - 1 - _c[max(j-(ri[i]<<1)+1,-1)]);
		i += ri[i];
	} cout << ans;
}