#include <bits/stdc++.h>
using namespace std;

constexpr int S(int x) {
	return x + 2;
}

namespace Main {
	const int N = 1e6;
	const int MOD = 1e9 + 7;
	vector<int> graph1[S(N)], graph2[S(N)], graph3[S(N)], graph4[S(N)]; // ԭͼ����ͼ�������ͼ�������ͼ 
	bitset<S(N)> mark;
	vector<int> s;
	int id[S(N)]; // SCC ��� 
	
	void dfs(int x) {
		mark[x] = true;
		for (auto y : graph1[x]) {
			if (!mark[y]) {
				dfs(y);
			}
		}
		s.push_back(x);
	}
	
	int f[S(N)], g[S(N)], in1[S(N)], in2[S(N)]; // hash �С��ؼ��㡱 

	
	void dfs2(int x, int tag) {
		id[x] = tag;
		for (auto y : graph2[x]) {
			if (id[y] == 0) {
				dfs2(y, tag);
			} else if (id[y] != tag) {
				graph3[id[y]].push_back(tag);
				graph4[tag].push_back(id[y]);
				in1[tag]++;
				in2[id[y]]++;
			}
		}
	}
	
	
	void main() {
		freopen("goood.in", "r", stdin);
		freopen("goood.out", "w", stdout);
		int n, m, x, y;
		cin >> n >> m;
		for (int i = 1; i <= m; ++i) {
			cin >> x >> y;
			graph1[x].push_back(y);
			graph2[y].push_back(x);
		}
		for (int i = 1; i <= n; ++i) {
			if (!mark[i]) {
				dfs(i);
			}
		}
		int cnt = 0;
		reverse(s.begin(), s.end());
		for (auto i : s) {
			if (id[i] == 0) {
				dfs2(i, ++cnt);
			}
		}
//		cout << "id: ";
//		for (int i = 1; i <= n; ++i) {
//			cout << id[i] << ' ';
//		}
//		cout << endl;
//		cout << "in1: ";
//		for (int i = 1; i <= cnt; ++i) {
//			cout << in1[i] << ' ';
//		}
//		cout << endl;
//		cout << "in2: ";
//		for (int i = 1; i <= cnt; ++i) {
//			cout << in2[i] << ' ';
//		}
//		cout << endl;
		vector<int> output;
		bitset<S(N)> good;
		for (int i = 1; i <= cnt; ++i) {
			if (in1[i] == 0) {
				good[i] = true; // û����ȵ� SCC �϶��Ƿ�ˮ���� 
				in1[i]++;
				graph3[0].push_back(i); // ����Դ��
			}
			if (graph3[i].empty()) {
				good[i] = true; // ����Ϊ 0 ����ĩ�����Ϊ 0 �� 
				in1[cnt + 1]++;
				graph3[i].push_back(cnt + 1); // �������
			}
			if (in2[i] == 0) { // �����ͼҲ��ô�� 
				in2[i]++;
				graph4[0].push_back(i); 
			}
			if (graph4[i].empty()) {
				in2[cnt + 1]++;
				graph4[i].push_back(cnt + 1);
			}
		}
//		cout << "graph4: ------------" << endl;
//		for (int i = 0; i <= cnt + 1; ++i) {
//			for (auto y : graph4[i]) {
//				cout << i << ' ' << y << endl;
//			}
//		}
//		cout << "--------------------" << endl;
//		cout << "already in good: ";
//		for (int i = 1; i <= cnt; ++i) {
//			if (good[i]) {
//				cout << i << ' ';
//			}
//		}
//		cout << endl;
		f[0] = 1;
		g[0] = 1;
		deque<int> q;
		
		q.push_back(0); 
		while (!q.empty()) { // ����������� f 
			int x = q.front();
			q.pop_front();
			for (auto y : graph3[x]) {
				(f[y] += f[x]) %= MOD;
				if (--in1[y] == 0) {
					q.push_back(y);
				}
			}
		}
		q.push_back(0);
		while (!q.empty()) { // ����������� g
			int x = q.front();
			q.pop_front();
			for (auto y : graph4[x]) {
				(g[y] += g[x]) %= MOD;
				if (--in2[y] == 0) {
					q.push_back(y);
				}
			}
		}
		
//		cout << "f(has 0 and cnt + 1): ";
//		for (int i = 0; i <= cnt + 1; ++i) {
//			cout << f[i] << ' ';
//		}
//		cout << endl;
//		cout << "g(has 0 and cnt + 1): ";
//		for (int i = 0; i <= cnt + 1; ++i) {
//			cout << g[i] << ' ';
//		}
//		cout << endl;
		for (int i = 1; i <= cnt; ++i) {
			if ((long long) f[i] * g[i] % MOD == f[cnt + 1]) {
				good[i] = true;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (good[id[i]]) {
				output.push_back(i);
			}
		}
		sort(output.begin(), output.end());
		cout << output.size() << endl;
		for (auto i : output) {
			cout << i << ' ';
		} 
	}
}

int main() {
	Main::main();
	return 0;
}
