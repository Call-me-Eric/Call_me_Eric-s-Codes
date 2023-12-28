#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	rep(i, 1, (int)1e7) {
		cerr << "#" << i << "...";
		int n = mtrnd() % 20 + 1;
		int k = mtrnd() % (n+1);
		char cmd[1000];
		sprintf(cmd, "echo %d %d > in", n, k);
		system(cmd);
		assert(!system("./bf.exe < in > ans"));
		assert(!system("./ur.exe < in > out"));
		assert(!system("./checker.exe in out ans"));
	}

	return 0;
}
