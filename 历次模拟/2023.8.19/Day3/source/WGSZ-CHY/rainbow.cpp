#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 2e3 + 6;
const int M = 5e6 + 6;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, m;
int a[N][N];
int vis[M];
signed main() {
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) a[i][j] = read();
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			ans++;
			vis[a[i][j]] = 1;
			int mxl = 1;
//			if(i == 1 && j == 2)
			for(int len = 1; i + len <= n && j + len <= m; len++) {
				if(vis[a[i + len][j]]) goto End;
				vis[a[i + len][j]] = 1;
//					cout << a[i + len][j] << ' ' << a[i][j + len] << ' ' << vis[a[i + len][j]] << ' ' << vis[a[i][j + len]];
				if(vis[a[i][j + len]]) goto End;
				vis[a[i][j + len]] = 1;
				mxl = max(mxl, len);
				for(int I = i; I <= i + len - 1; I++)
					if(a[I][j + len - 1] != a[I + 1][j + len]) goto End;
				for(int J = j; J <= j + len - 1; J++)
					if(a[i + len - 1][J] != a[i + len][J + 1]) goto End;
				ans++;
//				cout << i << ' ' << j << ' ' << len << endl;
			}

End:
//			memset(vis, 0, sizeof(vis));
			mxl++;
			for(int I = i; I <= i + mxl; I++) vis[a[I][j]] = 0;
			for(int J = j; J <= j + mxl; J++) vis[a[i][J]] = 0;
		}
	printf("%lld\n", ans);
	return 0;
}
/*
5 5
1 3 4 5 1
3 4 5 1 9
4 5 1 9 4
5 1 9 4 10
1 9 4 10 1

5 5
1 9 4 10 1
5 1 9 4 10
4 5 1 9 4
3 4 5 1 9
1 3 4 5 1
*/

