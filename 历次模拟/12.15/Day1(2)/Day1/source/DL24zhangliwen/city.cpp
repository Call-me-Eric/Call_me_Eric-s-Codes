#include <bits/stdc++.h>
using namespace std; 
const int P = 22222223; 

int n, m, a[105], b[105]; 
int f[105][1 << 8]; 

int main(void) {
    scanf("%d%d", &n, &m); 
    for (int i = 0; i < n; ++i) scanf("%d", a + i); 
    for (int i = 1; i <= m; ++i) scanf("%d", b + i); 
    f[0][0] = 1; 
    for (int i = 1; i <= m; ++i) for (int j = 0; j < 1 << n; ++j) {
        for (int k = j; k < 1 << n; k = k + 1 | j) {
            int r1 = f[i - 1][j], r2 = f[i - 1][j]; 
            for (int l = 0; l < n; ++l) {
                if (j >> l & 1) r1 = 1ll * r1 * min(a[l] + 1, b[i]), r2 = 1ll * r2 * min(a[l] + 1, b[i] + 1); // 允许范围内随便
                
                else r1 = 1ll * r1 * min(a[l] + 1, b[i]), r2 = 1ll * r2 * min(a[l] + 1, b[i] + 1); 
            }
            f[i][k] = (f[i][k] + r2 - r1) % P; 
        }
        printf("f[%d][%d] = %d\n", i, j, f[i][j]); 
    }
    if (f[m][(1 << n) - 1] == 0) puts("No solution!"); 
    else printf("%d\n", f[m][(1 << n) - 1]); 
    return 0; 
}