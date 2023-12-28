# include <cstdio>
# include <vector>
# include <algorithm>
# include <functional>

struct Mat {
	int N, M;
	int arr[11][11];
	
	Mat() {}
	Mat(int _N, int _M, int val = 0) {
		N = _N, M = _M;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				arr[i][j] = (i == j) ? val : 0;
			}
		}
	}
	
	friend Mat operator* (const Mat &A, const Mat &B) {
		Mat res(A.N, B.M);
		for(int i = 1; i <= res.N; ++i) {
			for(int k = 1; k <= A.M; ++k) {
				for(int j = 1; j <= res.M; ++j) {
					res.arr[i][j] = res.arr[i][j] ^ (A.arr[i][k] & B.arr[k][j]);
				}
			}
		}
		
		return res;
	}
};

Mat quickPow(Mat x, int k) {

	Mat res(x.N, x.N, 1);
	for (; k; k >>= 1) {
		if(k & 1) {
			res = res * x;
		} 
		x = x * x;
	}

	return res;
}

int main() {

	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);

	int n;
  scanf("%d", &n);

  Mat a(n, n);

  for (int i = 1; i <= n; ++i) {
    char s[11];
    scanf("%s", s + 1);
    for (int j = 1; j <= n; ++j) a.arr[i][j] = s[j] - '0';
  }

  Mat b(n, 1);
  
  char s[11];
  scanf("%s", s + 1);

  for (int i = 1; i <= n; ++i) {
    b.arr[i][1] = s[i] - '0';
  }

  int qwq;
  scanf("%d", &qwq);

  for (int i = 1; i <= qwq; ++i) {
    int x; scanf("%d", &x);
    Mat c = quickPow(a, x); c = c * b;
    for (int j = 1; j <= n; ++j) printf("%d%c", c.arr[j][1], " \n"[j == n]);
  }

	return 0;
}