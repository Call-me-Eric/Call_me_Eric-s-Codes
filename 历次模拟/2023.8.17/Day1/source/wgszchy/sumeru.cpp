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
const double eps = 1e-8;
const int N = 1e5 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 1e9 + 7;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int T;
double m[M][M];
double a[M][M];
void gauss() {
	for(int i = 1; i <= 3; i++) {
		int id = i;
		for(int j = i + 1; j <= 3; j++) if(fabs(m[id][i]) < fabs(m[j][i])) id = j;
		for(int j = 1; j <= 4; j++) swap(m[i][j], m[id][j]);
		if(fabs(m[id][i]) < eps) m[id][i]=0;
		for(int j = 1; j <= 3; j++)
			if(j != i) {
				double tmp = m[j][i] / m[i][i];
				for(int k = i + 1; k <= 4; k++) m[j][k] -= m[i][k] * tmp;
			}
	}
	for(int i = 1; i <= 3; i++) {
		double ans = m[i][4] / m[i][i];
//		printf("%.2lf\n", ans);
		if(ans < 0) {
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}
signed main() {
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
	srand(time(0));
	T = read();
	while(T--) {
		for(int i = 1; i <= 4; i++)
			for(int j = 1; j <= 3; j++) scanf("%lf", &a[i][j]);
		for(int i = 1; i <= 3; i++)
			for(int j = 1; j <= 4; j++) m[i][j] = a[j][i];
		gauss();
	}
	return 0;
}
/*
3
0 4 2 1 0 2 2 0 0 4 1 0
0 3 4 1 2 1 4 4 2 0 4 0
0 2 0 2 4 0 0 3 4 0 3 2
*/
