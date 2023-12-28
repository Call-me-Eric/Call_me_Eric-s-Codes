#include <iostream>
#include <cstdio>
#include <math.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 20, M = (1 << 16) + 10;

int fa[N], S[N][N];
bool f[N][M];

int n, over;

int main() {
	freopen("decoration.in", "r", stdin);
	freopen("decoration.out", "w", stdout);
	
	scanf("%d", &n);
	
	for (int i = 2; i <= n; ++ i) 
		scanf("%d", &fa[i]);
		
	for (int i = 1; i <= n; ++ i)
		for (int j = 1, k = i; j <= n; ++ j, k = fa[k]) {
			if (k)
				S[i][j] = S[i][j - 1] ^ (1 << (k - 1)); 
			else 
				S[i][j] = S[i][j - 1];
		}
		
	for (int x, i = 1; i <= n; ++ i) {
		scanf("%d", &x);
		over += (1 << (i - 1)) * x;
	}
		
	f[1][0] = 1;
	
	for (int i = 1; i <= n; ++ i) {
		if (f[i][over]) {
			printf("%d\n", i - 1);
			return 0;
		}
		
		for (int s = 0; s < (1 << n); ++ s) {
			if (! f[i][s])
				continue;
			
			f[i + 1][s] = 1;
			
			for (int j = 1; j <= n; ++ j)
				f[i + 1][s ^ S[j][i]] = 1;
		}
	}
	
	return 0;
} 
