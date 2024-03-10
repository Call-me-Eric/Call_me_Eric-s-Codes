// 什么 b 递推。/qd
// 卡常。/oh
// 32 位下没有 __int128。/cf

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

using i64 = long long;
const i64 P = 998244353;

inline i64 rd() {
	i64 x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

inline i64 fpow(i64 b, i64 p) {
	p %= P - 1; i64 res = 1;
	for(; p; b = b * b % P, p >>= 1) {
		if(p & 1) res = res * b % P;
	}
	return res;
}

struct mat { i64 m11, m12, m21, m22; };
inline mat operator*(const mat &A, const mat &B) {
	return {
		(A.m11 * B.m11 % P + A.m12 * B.m21 % P) % P,
		(A.m11 * B.m12 % P + A.m12 * B.m22 % P) % P,
		(A.m21 * B.m11 % P + A.m22 * B.m21 % P) % P,
		(A.m21 * B.m12 % P + A.m22 * B.m22 % P) % P,
	};
}
struct vec { i64 m1, m2; };
vec operator*(const vec &a, const mat &B) {
	return {
		(a.m1 * B.m11 % P + a.m2 * B.m21 % P) % P,
		(a.m1 * B.m12 % P + a.m2 * B.m22 % P) % P,
	};
}

i64 n, m;
void solve() {
	n = rd() % P, m = rd();

	if(n == 1) return puts("0"), void();
	if(n == 2) return puts("1"), void();

	mat A = {(n - 2) % P, 0, (2 * n % P + P - 2) % P, n};
	vec b = {0, 1};

	i64 p = m;
	for(; p; A = A * A, p >>= 1) {
		if(p & 1) b = b * A;
	}

	printf("%lld\n", b.m1 * fpow(fpow(n, m), P - 2) % P);
}

int main() {
	freopen("poster.in", "r", stdin), freopen("poster.out", "w", stdout);

	int T = rd();
	while(T--) solve();
	return 0;
}
