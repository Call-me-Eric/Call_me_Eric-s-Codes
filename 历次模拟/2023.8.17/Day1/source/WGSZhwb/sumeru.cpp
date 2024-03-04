#include <cstdio>
#include <algorithm>

using f64 = double;
const int N = 5;

int T;

f64 a[N + 5][N + 5];
void gauss() {
	for(int i = 1; i <= 3; i++) {
		int p = i;
		for(int j = i + 1; j <= 3; j++) {
			if(a[j][i] > a[p][i]) p = j;
		}
		if(p != i) std::swap(a[i], a[p]);
		for(int j = 1; j <= 3; j++) {
			if(j == i) continue;
			f64 t = a[j][i] / a[i][i];
			for(int k = 1; k <= 4; k++) {
				a[j][k] -= t * a[i][k];
			}
		}
	}
}

void solve() {
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= 3; j++) {
			scanf("%lf", &a[j][i]);
		}
	}
//	for(int i = 1; i <= 3; i++) {
//		for(int j = 1; j <= 4; j++) {
//			printf("%lf%c", a[i][j], " \n"[j == 4]);
//		}
//	}
	gauss();
//	for(int i = 1; i <= 3; i++) {
//		for(int j = 1; j <= 4; j++) {
//			printf("%lf%c", a[i][j], " \n"[j == 4]);
//		}
//	}
	for(int i = 1; i <= 3; i++) {
		for(int j = 1; j <= 4; j++) {
			if(std::isnan(a[i][j]) || std::isinf(a[i][j])) return puts("NO"), void();
		}
	}
	for(int i = 1; i <= 3; i++) {
		if(a[i][i]*a[i][4] < 0) return puts("NO"), void();
	}
	puts("YES");
}

int main() {
	freopen("sumeru.in", "r", stdin), freopen("sumeru.out", "w", stdout);

	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
/*
1
3 1 0 4 0 1 1 4 4 1 2 2

1
1 0 3 0 0 4 1 0 1 4 4 3

1
0 2 2 0 4 1 0 2 4 0 2 1

*/
