#include <cstdio>
#include <vector>
#include <cmath>

const int N = 1e5;

int n, m, a[N + 5];
struct Q { int l, id; }; std::vector<Q> q[N + 5]; int ans[N + 5];

int b[N + 5], bsiz;
int bl[N + 5], br[N + 5];
int seq[N + 5], sum[N + 5];
void initblk() {
	bsiz = sqrt(n);
	for(int i = 1; i <= n; i++) b[i] = (i - 1) / bsiz + 1;
	for(int i = 1; i <= b[n]; i++) bl[i] = (i - 1) * bsiz + 1;
	for(int i = 1; i <= b[n] - 1; i++) { br[i] = i * bsiz; } br[b[n]] = n;
}
int ctu, ctq;
void upd(int x, int d) {
	seq[x] += d, sum[b[x]] += d;
}
int que(int l, int r) {
	int res = 0;
	if(b[l] == b[r]) {
		for(int i = l; i <= r; i++) res += seq[i];
		return res;
	}
	for(int i = l; i <= br[b[l]]; i++) res += seq[i];
	for(int i = b[l] + 1; i <= b[r] - 1; i++) res += sum[i];
	for(int i = bl[b[r]]; i <= r; i++) res += seq[i];
	return res;
}

int pos[N + 5];

int main() {
	freopen("liyue.in", "r", stdin), freopen("liyue.out", "w", stdout);

	scanf("%d", &n); for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1, l, r; i <= m; i++) {
		scanf("%d%d", &l, &r);
		q[r].push_back({l, i});
	}

	for(int i = 1; i <= n; i++) pos[a[i]] = i;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j * j <= n * 2; j++) {
			if(j * j - a[i] > 0 && j * j - a[i] <= n && pos[j * j - a[i]] < i) {
				upd(pos[j * j - a[i]], 1);
			}
		}
		for(auto qu : q[i]) {
			ans[qu.id] = que(qu.l, i);
		}
	}

	for(int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
