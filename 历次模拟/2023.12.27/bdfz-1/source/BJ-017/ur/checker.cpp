#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

const int N = 2e5 + 5;
const long double pi = acos(-1);
const long double eps = 1e-8;

int n, k;
int a[N];
char str[N];

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	assert(argc == 4);
	ifstream inf(argv[1]);
	ifstream ouf(argv[2]);
	ifstream anf(argv[3]);
	inf >> n >> k;
	ouf >> str + 1;
	assert(n == strlen(str + 1));
	rep(i, 1, n) a[i] = str[i]-'0';
	long double sx = 0, sy = 0;
	rep(i, 1, n) if(a[i]) {
		long double theta = 2 * pi / n * i;
		sx += cos(theta);
		sy += sin(theta);
	}
	assert(fabs(sx) < eps && fabs(sy) < eps);
	int sum = 0;
	assert(sum <= k);
	rep(i, 1, n) sum += a[i];
	int jans; anf >> jans;
	assert(jans == sum);
	cerr << "ok n = " << n << ", k = " << k << ", sum = " << sum << "\n";

	return 0;
}
