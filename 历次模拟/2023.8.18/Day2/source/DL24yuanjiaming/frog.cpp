#include <iostream>
using namespace std;
constexpr int MAXN = 10000007;
int x1[MAXN], x2[MAXN], x3[MAXN], x4[MAXN], x5[MAXN];
int f[MAXN], A[MAXN];
int n;
inline void read(int &temp) { cin >> temp; }
inline bool check(int a, int b) {
	if (x1[a] < x1[b])  return false;
	if (x2[a] < x2[b])  return false;
	if (x3[a] < x3[b])  return false;
	if (x4[a] < x4[b])  return false;
	if (x5[a] < x5[b])  return false;
	return true;
}
int main() {
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	for (int i = 1; i <= n; ++i)  read(x1[i]), read(x2[i]), read(x3[i]), read(x4[i]), read(x5[i]), read(A[i]);
//	cerr << "ok" << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j)  if (check(i, j))  f[i] = max(f[i], f[j]);
		f[i] += A[i];
	}
	for (int i = 1; i <= n; ++i)  cout << f[i] << endl;
	return 0;
}
