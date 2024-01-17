#include <tuple> 
#include <queue>
#include <math.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10, inf = 1e9 + 10;

template <class T>

void read(T &n) {
	n = 0;
	char c = getchar();
	
	while (c < '0' || c > '9')
		c = getchar();
		
	while (c >= '0' && c <= '9')
		n = n * 10 + c - '0',
		c = getchar();
	
	return;
}

vector<tuple<int, int, int> > e[N];

priority_queue<pair<int, int> > q, p;

int h[N], f[N], op[N];
bool vis[N];

int n, m;

int main() {
	freopen("lunch.in", "r", stdin);
	freopen("lunch.out", "w", stdout);
	
	read(n), read(m);
	
	for (int x, y, l, r, i = 1; i <= m; ++ i) {
		read(x), read(y), read(l), read(r);
		e[x].emplace_back(y, l, r);
		e[y].emplace_back(x, l, r);
	}
	
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", &op[i]);
		
		if (op[i] == -1) {
			h[i] = inf;
			q.push(make_pair(h[i], i));
		}
			
		if (i != 1)
			f[i] = inf;
	}
	
	while (! q.empty()) {
		int v, l, r, u = q.top().second; q.pop();
		
		if (vis[u])
			continue;
		
		vis[u] = 1;
		
		for (auto i : e[u]) {
			v = get<0>(i), l = get<1>(i), r = get<2>(i);
			
			if (h[u] > r  && h[v] <= l) {
				h[v] = l + 1;
				q.push(make_pair(h[v], v));
			}
		}
	}

	if (h[1] >= 1) 
		return printf("Impossible\n"), 0;
		
	p.push(make_pair(0, 1));
	memset(vis, 0, sizeof vis);
	
	while (! p.empty()) {
		int v, l, r, res, u = p.top().second; p.pop();
		
		if (vis[u])
			continue;
			
		vis[u] = 1;
		
		for (auto i : e[u]) {
			v = get<0>(i), l = get<1>(i), r = get<2>(i);
			res = max(l, max(f[u], h[v]));
			
			if (res < f[v] && res <= r) {
				f[v] = res;
				p.push(make_pair(-f[v], v));
			}
		}
	} 
	
	for (int i = 1; i <= n; ++ i)
		if (op[i] == 1 && f[i] >= inf) 
			return printf("Impossible\n"), 0;
			
	printf("JJXSM\n");
	return 0;
}
