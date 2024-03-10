#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 1e5 + 5;
const int M = 20;
const int V = 1e7;
const int mod = 1e9 + 7;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, m;
int a[N];
void subtask1() {
	m = read();
	while(m--) {
		int l, r;
		l = read(), r = read();
		int ans = 0;
		for(int i = sqrt(2 * l) + 1; i * i / 2 <= r; i++) {
//			cout<<i<<endl;
			if(i * i % 2 == 1) ans += min(r - i * i / 2, i * i / 2 - l + 1);
			else ans += min(r - i * i / 2, i * i / 2 - l);
		}
		printf("%lld\n", ans);
	}
	exit(0);
}
int bel[N];
struct query {
	int l, r, id;
	bool operator<(query t)const {
		if(bel[t.l] == bel[l]) return r < t.r;
		return bel[l] < bel[t.l];
	}
} q[N];
int ans[N];
int cnt[N];
int res;
void add(int x) {
	for(int i = sqrt(a[x]) + 1; i * i - a[x] <= n; i++) res += cnt[i * i - a[x]];
	cnt[a[x]]++;
}
void del(int x) {
	cnt[a[x]]--;
	for(int i = sqrt(a[x]) + 1; i * i - a[x] <= n; i++) res -= cnt[i * i - a[x]];
}
void subtask2() {
	m = read();
	for(int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;
	int bsiz = sqrt(n);
	for(int i = 1; i <= n; i++) bel[i] = (i - 1) / bsiz + 1;
	sort(q + 1, q + 1 + m);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(l < q[i].l) del(l++);
		while(r > q[i].r) del(r--);
		ans[q[i].id] = res;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	exit(0);
}
signed main() {
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	int ok = 1;
	for(int i = 1; i <= n; i++) if(a[i] != i) ok = 0;
	if(ok) subtask1();
	subtask2();
	return 0;
}
/*
10
1 2 3 4 5 6 7 8 9 10
1
2 6
*/
