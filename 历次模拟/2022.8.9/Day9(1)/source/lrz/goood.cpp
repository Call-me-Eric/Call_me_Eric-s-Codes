#include <cstdio>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 1e6;
const int MAXM = 1e6;

int n, m;
int x[2 * MAXM + 10], y[2 * MAXM + 10];

int head[2 * MAXN + 10], numEdge;
struct Edge {
	int nxt, to;
}edge[2 * MAXM + 10];

void addEdge(int x, int y) {

	++numEdge;
	edge[numEdge].nxt = head[x];
	edge[numEdge].to = y;
	head[x] = numEdge;

	return;
}

int dfn[2 * MAXN + 10], low[2 * MAXN + 10], scc[2 * MAXN + 10], numScc, cnt;
std::stack<int>sta;
std::vector<int>Scc[2 * MAXN + 10];

void tarjan(int u) {

	dfn[u] = low[u] = ++cnt;
	sta.push(u);
	for(int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if(!dfn[k]) {
			tarjan(k);
			low[u] = std::min(low[u], low[k]);
		}
		else if(!scc[k]) {
			low[u] = std::min(low[u], dfn[k]);
		}
	}

	if(dfn[u] == low[u]) {
		int t;
		++numScc;
		do {
			scc[t = sta.top()] = numScc;
			Scc[numScc].push_back(t);
			sta.pop();
		}while(t != u);
	}

	return;
}

int fa[2 * MAXN + 10];

int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void unity(int x, int y) {
	fa[find(x)] = find(y);
}

int in[2 * MAXN + 10];

void rebuild() {

	numEdge = 0;
	std::memset(edge, 0, sizeof(struct Edge) * (2 * MAXM + 10));
	std::memset(head, 0, sizeof(head));
	
	for(int i = 1; i <= numScc; ++i) {
		fa[i] = i;
	}
	for(int i = 1; i <= m; ++i) {
		if(find(scc[x[i]]) != find(scc[y[i]])) {
			++in[scc[y[i]]];
			unity(scc[x[i]], scc[y[i]]);
			addEdge(scc[x[i]], scc[y[i]]);
		}
	}

	return;
}

int rank[2 * MAXN + 10];

void toposort() {

	std::queue<int>que;
	for(int i = 1; i <= numScc; ++i) {
		if(!in[i]) {
			que.push(i);
			rank[i] = 1;
		}
	}
	
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int k = edge[i].to;
			--in[k];
			if(!in[k]) {
				que.push(k);
				rank[k] = rank[u] + 1;
			}
		}
	}

	return;
}

int main() {

	freopen("goood.in", "r", stdin);
	freopen("goood.out", "w", stdout);

	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d %d", &x[i], &y[i]);
		addEdge(x[i], y[i]);
	}
	
	for(int i = 1; i <= n; ++i) {
		if(!dfn[i]) {
			tarjan(i);
		}
	}
	
	rebuild();
	toposort();
	std::vector<std::pair<int, int> >vec;
	for(int i = 1; i <= numScc; ++i) {
		if(!rank[i]) {
			puts("0");
			return 0;
		}
		vec.push_back(std::make_pair(rank[i], i));
	}
	std::sort(vec.begin(), vec.end());
	
	std::vector<int>vecc;
	for(int i = 0; i < vec.size(); ++i) {
		if(i == 0 || i == vec.size() - 1) {
			if(!(i == 0 && vec[i + 1].first == vec[i].first || i == vec.size() - 1 && vec[vec.size() - 1].first == vec[vec.size() - 2].first)) {
				vecc.push_back(vec[i].second);
			}
		}
		else if(vec[i].first != vec[i - 1].first && vec[i].first != vec[i + 1].first) {
			vecc.push_back(vec[i].second);
		}
	}
	
	std::vector<int>veccc;
	for(int i = 0; i < vecc.size(); ++i) {
		for(int j = 0; j < Scc[vecc[i]].size(); ++j) {
			veccc.push_back(Scc[vecc[i]][j]);
		}
	}
	printf("%d\n", veccc.size());
	std::sort(veccc.begin(), veccc.end());
	for(int i = 0; i < veccc.size(); ++i) {
		printf("%d ", veccc[i]);
	}

	return 0;
}
