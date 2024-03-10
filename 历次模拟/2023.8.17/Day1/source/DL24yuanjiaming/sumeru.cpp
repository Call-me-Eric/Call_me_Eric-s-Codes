#include <iostream>
using namespace std;
int a[7][7];
int T;
inline void read(int &temp) { cin >> temp; }
inline void work() {
	for (int i = 1; i <= 4; ++i) 
		for (int j = 1; j <= 3; ++j)  read(a[i][j]);
	int a1 = a[2][1] * a[1][2] - a[1][1] * a[2][2], b1 = a[3][1] * a[1][2] - a[1][1] * a[3][2], c1 = a[4][1] * a[1][2] - a[4][2] * a[1][1];
	int a2 = a[2][1] * a[1][3] - a[1][1] * a[2][3], b2 = a[3][1] * a[1][3] - a[1][1] * a[3][3], c2 = a[4][1] * a[1][3] - a[4][3] * a[1][1];
	if ((a2 * c1 - c2 * a1) * (b1 * a2 - b2 * a1) < 0 || (!(a2 * b1 - a1 * b2) && (a2 * c1 - c2 * a1)))  return cout << "NO" << endl, void();
	if ((b2 * c1 - c2 * b1) * (a1 * b2 - a2 * b1) < 0 || (!(a2 * b1 - a1 * b2) && (b2 * c1 - c2 * b1)))  return cout << "NO" << endl, void();
	a1 = a[2][2] * a[1][1] - a[1][2] * a[2][1], b1 = a[3][1] * a[2][2] - a[3][2] * a[2][1], c1 = a[4][1] * a[2][2] - a[4][2] * a[2][1];
	a2 = a[1][2] * a[2][3] - a[1][3] * a[2][2], b2 = a[3][2] * a[2][3] * a[3][3] * a[2][2], c2 = a[4][2] * a[2][3] - a[4][3] * a[2][2];
	if ((a2 * c1 - c2 * a1) * (b1 * a2 - b2 * a1) < 0 || (!(a2 * b1 - a1 * b2) && (a2 * c1 - c2 * a1)))  return cout << "NO" << endl, void();
	if ((b2 * c1 - c2 * b1) * (a1 * b2 - a2 * b1) < 0 || (!(a2 * b1 - a1 * b2) && (b2 * c1 - c2 * b1)))  return cout << "NO" << endl, void();
	cout << "YES" << endl;
	//No, commander.
}
int main() {
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(T);
	while (T--)  work();
	return 0;
}
