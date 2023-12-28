
#include<cstdio>
#define mo 9973

using namespace std;

struct matrix {
	int n, m;
	int a[11][11];
}a, one, A;
int T, n, m, k, x, y, ans;

int jia(int x, int y) {
	return x + y >= mo ? x + y - mo : x + y;
}

int mul(int x, int y) {
	int re = x * y;
	if (re > mo) re = re - re / mo * mo;
	return re;
}

matrix operator *(matrix x, matrix y) {//矩阵乘法
	matrix re;
	re.n = x.n; re.m = y.m;
	for (int i = 1; i <= re.n; i++)
		for (int j = 1; j <= re.m; j++)
			re.a[i][j] = 0;
	for (int k = 1; k <= x.m; k++)
		for (int i = 1; i <= re.n; i++)
			for (int j = 1; j <= re.m; j++)
				re.a[i][j] = jia(re.a[i][j], mul(x.a[i][k], y.a[k][j]));
	return re;
}

matrix jzksm(matrix x, int y) {
	matrix re = one;
	while (y) {
		if (y & 1) re = re * x;
		x = x * x;
		y >>= 1;
	} 
	return re;
}

int ksm(int x, int y) {
	int re = 1; x = mul(x, 1);
	while (y) {
		if (y & 1) re = mul(re, x);
		x = mul(x, x);
		y >>= 1;
	}
	return re;
}

int phi(int n) {//求 phi
	int re = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			re = re / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) re = re / n * (n - 1);
	return mul(re, 1); 
}

int work(int d) {
	A = jzksm(a, n / d - 1);
	int re = 0;
	for (int i = 1; i <= m; i++)//直接上 DP 的结果
		for (int j = 1; j <= m; j++){
			if (a.a[i][j])//记得首尾要连接，所以要首尾能在一起
				re = jia(re, A.a[i][j]);
            printf("(%d,%d) = %d\n",i,j,re);
        }
    printf("ans = %d\n",ans);
	ans = jia(ans, mul(re, phi(d)));//直接乘上取这个值的可能性（phi）
    return 0;
}

int main() {
	for (int i = 1; i <= 10; i++) one.a[i][i] = 1;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &k);
		
		one.n = one.m = m;
		a.n = a.m = m;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				a.a[i][j] = 1;
		for (int i = 1; i <= k; i++) {
			scanf("%d %d", &x, &y);
			a.a[x][y] = a.a[y][x] = 0;
		}
		
		ans = 0;
		for (int i = 1; i * i <= n; i++)
			if (n % i == 0) {//枚举 gcd(i,n) 的取值
				work(i); if (n / i != i) work(n / i);
			}
		printf("%d\n",ans);
		ans = ans * ksm(n, mo - 2) % mo;
		printf("%d\n", ans);
	}
	
	return 0;
}
