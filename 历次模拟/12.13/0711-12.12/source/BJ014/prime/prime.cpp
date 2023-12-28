#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull B = 0xAE3803;

const long long mod = 998244353;

const int P[26] = {2,
3,
5,
7,
11,
19,
41,
61,
89,
409,
449,
499,
881,
991,
6469,
6949,
9001,
9049,
9649,
9949,
60649,
666649,
946669,
60000049,
66000049,
66600049
};
const int M[6] = {1, 4, 6, 8, 9, 0};

int a[25][25], len[25];
struct Node {
	int mct[25];
	Node() {
		memset(mct, 0, sizeof(mct));
	}
	inline ull Hashval() {
		ull hsv = 0;
		for (int i = 1;i <= 22;i++) hsv = hsv * B + mct[i];
		return hsv;
	}
};
queue <Node> que;
map <ull, int> mp;

int g[111][6];
long long dp[2][111][3]; // 0: <, 1: =, 2: >
int slen, n[100055], ssz;
char str[100055];

inline Node Nxt(Node cur, int x) {
	for (int i = 1;i <= 22;i++) {
		if (a[i][cur.mct[i] + 1] == x) cur.mct[i]++;
	}
	return cur;
}

inline bool Chk(Node cur) {
	for (int i = 1;i <= 22;i++) {
		if (cur.mct[i] == len[i]) return 0;
	}
	return 1;
}

inline void Prefix() {
	for (int i = 4;i < 26;i++) {
		int x = P[i];
		while (x) {
			a[i - 3][++len[i - 3]] = x % 10;
			x /= 10;
		}
		//reverse(a[i - 3] + 1, a[i - 3] + len[i - 3] + 1);
	}
}

inline void Bfs() {
	memset(g, -1, sizeof(g));
	int cnt = 0;
	Node cur;
	for (int i = 1;i <= 22;i++) cur.mct[i] = 0;
	que.push(cur);
	mp[cur.Hashval()] = ++cnt;
	while (!que.empty()) {
		cur = que.front();
		que.pop();
		int cid = mp[cur.Hashval()];
		for (int i = 0;i < 6;i++) {
			Node nxt = Nxt(cur, M[i]);
			if (Chk(nxt) && !mp.count(nxt.Hashval())) {
				que.push(nxt);
				mp[nxt.Hashval()] = ++cnt;
			}
			g[cid][i] = mp[nxt.Hashval()];
		}
	}
	//cerr << cnt << endl;
	ssz = cnt;
}

inline void Add(long long &x, long long y) {
	x = (x + y >= mod ? x + y - mod : x + y);
}

inline long long Work() {
	memset(dp, 0, sizeof(dp));
	dp[0][1][1] = 1;
	for (int i = 0;i < slen;i++) {
		memset(dp[i + 1 & 1], 0, sizeof(dp[i + 1 & 1]));
		for (int j = 1;j <= ssz;j++) {
			for (int k = 0;k < 3;k++) {
				for (int x = 0;x < 6;x++) {
					if (g[j][x]) {
						if (M[x] == n[i + 1]) Add(dp[i + 1 & 1][g[j][x]][k], dp[i & 1][j][k]);
						else Add(dp[i + 1 & 1][g[j][x]][2 * (M[x] > n[i + 1])], dp[i & 1][j][k]);
					}
				}
			}
		}
	}
	long long ans = 0;
	for (int i = 1;i <= ssz;i++) {
		Add(ans, dp[slen & 1][i][0]);
		Add(ans, dp[slen & 1][i][1]);
	}
	return ans;
}

inline void Solve() {
	cin >> str + 1;
	slen = strlen(str + 1);
	for (int i = 1;i <= slen;i++) n[i] = str[slen - i + 1] - '0';
	for (int i = 1;i <= slen;i++) {
		if (n[i]) {
			n[i]--;
			break;
		}
		n[i] = 9;
	}
	long long ans = mod - Work();
	cin >> str + 1;
	slen = strlen(str + 1);
	for (int i = 1;i <= slen;i++) n[i] = str[slen - i + 1] - '0';
	ans = (ans + Work()) % mod;
	cout << (ans % mod + mod) % mod << "\n";
}

int main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Prefix();
	Bfs();
	int t;
	cin >> t;
	while (t--) {
		Solve();
	}
	return 0;
}
