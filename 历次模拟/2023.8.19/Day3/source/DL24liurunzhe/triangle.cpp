# include <cstdio>
# include <queue>
# include <vector>

const int MAXN = 100 + 5;

int n, k;

int a[MAXN << 1][MAXN << 1];

std::priority_queue<int, std::vector<int>, std::greater<int> > hp[MAXN][MAXN];

int main() {
	
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) scanf("%d", &a[i][j]);
	}
	hp[1][1].push(a[1][1]);
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			std::priority_queue<int, std::vector<int>, std::greater<int> > tmp;
			while (!hp[i - 1][j].empty()) {
				hp[i][j].push(hp[i - 1][j].top() + a[i][j]);
				tmp.push(hp[i - 1][j].top()); hp[i - 1][j].pop();
			}
			while (!tmp.empty()) hp[i - 1][j].push(tmp.top()), tmp.pop();
			while (!hp[i - 1][j - 1].empty()) {
				hp[i][j].push(hp[i - 1][j - 1].top() + a[i][j]);
				tmp.push(hp[i - 1][j - 1].top()); hp[i - 1][j - 1].pop();
			}
			while (!tmp.empty()) hp[i - 1][j - 1].push(tmp.top()), tmp.pop();
			while (hp[i][j].size() > k) hp[i][j].pop();
		}
	}
	std::priority_queue<int, std::vector<int>, std::greater<int> > res;
	for (int i = 1; i <= n; ++i) {
		while (!hp[n][i].empty()) {
			res.push(hp[n][i].top()), hp[n][i].pop();
		}
	}
	while (res.size() > k) res.pop();
	printf("%d\n", res.top());
	
	return 0;
}
