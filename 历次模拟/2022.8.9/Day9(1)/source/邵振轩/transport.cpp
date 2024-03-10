#include <bits/stdc++.h>
using namespace std;

constexpr int S(int x) {
	return x + 2;
}

namespace fhq {
	const int POOL = 1e6;
	
	class node {
	public:
		int p, size;
		long long v;
		node *ch[2];
	};
	
	node memPool[S(POOL)];
	node *memTop;
	node *rec[S(POOL)];
	int recTop;
	node *nil;
	
	typedef pair<node*, node*> PNN;
	
	node *newNode() {
		if (recTop) {
			return rec[recTop--];
		} else {
			return memTop++;
		}
	}
	
	node *newNode(long long v) {
		node *cur = newNode();
		cur->ch[0] = cur->ch[1] = nil;
		cur->v = v;
		cur->p = rand();
		cur->size = 1;
		return cur;
	}
	
	node *delNode(node *cur) {
		if (cur != nil) {
			rec[++recTop] = cur;
		}
	}
	
	class init {
	public:
		init() {
			memTop = memPool;
			recTop = 0;
			nil = newNode();
			nil->ch[0] = nil->ch[1] = nil;
			nil->size = 0;
		}
	} bminit;
	
	void maintain(node *cur) {
		if (cur == nil) {
			return;
		}
		cur->size = cur->ch[0]->size + cur->ch[1]->size + 1;
	}
	
	PNN split(node *cur, long long v) {
		if (cur == nil) {
			return {nil, nil};
		}
		if (v < cur->v) {
			PNN p = split(cur->ch[0], v);
			cur->ch[0] = p.second;
			maintain(cur);
			return {p.first, cur};
		} else {
			PNN p = split(cur->ch[1], v);
			cur->ch[1] = p.first;
			maintain(cur);
			return {cur, p.second};
		}
	}
	
	node *join(node *a, node *b) {
		if (a == nil) {
			return b;
		}
		if (b == nil) {
			return a;
		}
		if (a->p > b->p) {
			a->ch[1] = join(a->ch[1], b);
			maintain(a);
			return a;
		} else {
			b->ch[0] = join(a, b->ch[0]);
			maintain(b);
			return b;
		}
	}
	
	void destroy(node *cur) {
		if (cur == nil) {
			return;
		}
		destroy(cur->ch[0]);
		destroy(cur->ch[1]);
		delNode(cur);
	}
	
	void output(node *cur) {
		if (cur == nil) {
			return;
		}
		output(cur->ch[0]);
		cout << cur->v << ' ';
		output(cur->ch[1]);
	}
	
	class tree {
	public:
		node *root;
		
		tree() {
			root = nil;
		}
		
		void clear() {
			destroy(root);
			root = nil;
		}
		
		void insert(long long v) {
			PNN p = split(root, v);
			root = join(p.first, join(newNode(v), p.second));
		}
		
		int ge(long long v) { // >= v 的元素个数 
			PNN p = split(root, v - 1);
			int res = p.second->size;
			root = join(p.first, p.second);
			return res;
		}
	};
}


namespace Main {
	const int N = 2e5;
	const int U = 1e6;
	
	typedef pair<int, long long> PII;
	
	vector<PII> graph[S(N)];
	long long a[S(N)];
	int size[S(N)], n, ans; // f[i] 表示从 i 走到当前的根能剩多少容量
	fhq::tree tree;
	bitset<S(N)> mark;
	
	void getSize(int x, int p) {
		size[x] = 1;
		for (auto[y, c] : graph[x])  {
			if (y != p && !mark[y]) {
				getSize(y, x);
				size[x] += size[y];
			}
		}
	}
	
	PII getCenter(int x, int p, int tot) {
		int heavy = 0;
		PII best = {INT_MAX, 0};
		for (auto[y, c] : graph[x]) {
			if (y != p && !mark[y]) {
				best = min(best, getCenter(y, x, tot));
				heavy = max(heavy, size[y]);
			}
		}
		heavy = max(heavy, tot - size[x]);
		return min(best, {heavy, x});
	}
	
	void upd(int x, int p, int c, long long need, long long f) { // need 是父节点需要多少, f 是从父节点开始到根的路径有油就加剩的油 
		f += a[x] - c;
		need = max(need + c - a[x], 0ll);
		cout << "f: " << f << endl;
		if (need == 0) {
			tree.insert(f);
		}
		for (auto[y, c] : graph[x]) {
			if (y != p && !mark[y]) {
				upd(y, x, c, need, f);
			}
		}
	}
	
	void dfs(int x, int p, long long have, long long need) {
		ans += tree.ge(need);
		have += a[x];
		for (auto[y, c] : graph[x]) {
			if (y != p && !mark[y]) {
				if (have >= c) {
					dfs(y, x, have - c, need);
				} else {
					dfs(y, x, 0, need + c - have);
				}
			}
		}
	} 
	
	void solve(int x) {
//		cout << "solve(in): " << x << ' ' << ans << endl;
		getSize(x, 0);
		int rt = getCenter(x, 0, size[x]).second;
		mark[rt] = true;
		if (x == 1) {
			cout << "root: " << rt << endl;
			cout << "first time -------------"  << endl;
		}
		tree.insert(a[rt]); // 树根的油 
		for (auto[y, c] : graph[rt]) {
			if (!mark[y]) {
				dfs(y, rt, 0, c);
				upd(y, rt, c, 0, a[rt]); // 根结点的油归修改 
				if (x == 1) {
					cout << y << ": " << "ans: " << ans << endl;
					fhq::output(tree.root);
					cout << endl;
				}
			}
		}
		ans += tree.root->size; // 从子树中的节点到根节点 
		tree.clear();
		// 第一次树根的油已经算过了，这里就不再算了 
		reverse(graph[rt].begin(), graph[rt].end());
		if (x == 1) {
			cout << "second time -------------"  << endl;
		}
		for (auto[y, c] : graph[rt]) {
			if (!mark[y]) {
				dfs(y, rt, c, 0);
				upd(y, rt, c, 0, a[rt]); // 根结点的油归修改 
				if (x == 1) {
					cout << y << ": " << "ans: " << ans << endl;
					fhq::output(tree.root);
					cout << endl;
				}
			}
		}
		tree.clear();
		for (auto[y, c] : graph[rt]) {
			if (!mark[y]) {
				solve(y);
			}
		}
		mark[rt] = false;
//		cout << "solve(out): " << x << ' ' << ans << endl;
	}
	
	void main() {
		freopen("transport2.in", "r", stdin);
		freopen("transport.out", "w", stdout);
		int n, x, y, c;
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}
		for (int i = 1; i <= n - 1; ++i) {
			cin >> x >> y >> c;
			graph[x].emplace_back(y, c);
			graph[y].emplace_back(x, c); 
		}
		solve(1);
		cout << ans;
	}
}



int main() {
	Main::main();
	return 0;
} 
