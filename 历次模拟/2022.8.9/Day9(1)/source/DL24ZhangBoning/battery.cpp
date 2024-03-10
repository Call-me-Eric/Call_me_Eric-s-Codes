#include<bits/stdc++.h>
using namespace std;

#define FO(name) freopen(name".in","r",stdin);freopen(name".out","w",stdout)
#define TAG cout << "TAG" << endl

const int maxN = 60;
int MAP[maxN][maxN];
int AMAP[maxN][maxN];

char S[maxN][maxN];

int F[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};

inline int chk(char c) {
	if (c == '|' || c == '-') return 1;
	if (c == '.') return 0;
	if (c == '#') return -1;
	if (c == '\\') return 2;
	if (c == '/') return 3;
}

int N, M;

inline bool check(int xx, int yy, int to) {
	int x = xx, y = yy;
	int T = to;
	while (x >= 1 && x <= N && y >= 1 && y <= M) {
		if (MAP[x][y] == 1) return false;
		if (MAP[x][y] == 2) {
			T = 3 - T;
		} else if (MAP[x][y] == 3) {
			if (T == 0) T = 2;
			else if (T == 1) T = 3;
			else if (T == 2) T = 0;
			else if (T == 3) T = 1;
		}
		if (MAP[x][y] == -1) break;
		x = x + F[T][0];
		y = y + F[T][1];
	}
	x = xx, y = yy;
	T = to + 1;
	while (x >= 1 && x <= N && y >= 1 && y <= M) {
		if (MAP[x][y] == 1) return false;
		if (MAP[x][y] == 2) {
			T = 3 - T;
		} else if (MAP[x][y] == 3) {
			if (T == 0) T = 2;
			else if (T == 1) T = 3;
			else if (T == 2) T = 0;
			else if (T == 3) T = 1;
		}
		if (MAP[x][y] == -1) break;
		x = x + F[T][0];
		y = y + F[T][1];
	}
	return true;
}

struct Point {
	int x, y, fc;
	Point(int x, int y, int fc): x(x), y(y), fc(fc) {};
};

vector<Point> P;
int ANSS[maxN][maxN];

inline bool test() {
//	cout << " ---------" << endl;
	memset(AMAP, 0, sizeof(AMAP));
	for (auto i : P) {
		int x = i.x, y = i.y;
		int T = i.fc;
		while (x >= 1 && x <= N && y >= 1 && y <= M) {
//			cout << "At:" << x << "," << y << ",Fc=" << T << "M = " << MAP[x][y] << endl;
			x = x + F[T][1];
			y = y + F[T][0];
			
			if (MAP[x][y] == 1) {
//				TAG;
				return false;
			}
			if (MAP[x][y] == 2) {
				if(T == 0) T = 3;
				else if(T == 1) T = 2;
				else if(T == 2) T = 1;
				else if(T == 3) T = 0;
			} else if (MAP[x][y] == 3) {
				if (T == 0) T = 2;
				else if (T == 1) T = 3;
				else if (T == 2) T = 0;
				else if (T == 3) T = 1;
			}
			if (MAP[x][y] == -1) break;
			if (MAP[x][y] == 0) AMAP[x][y] = 1;
		}
		x = i.x, y = i.y;
		T = i.fc ^ 1;
		while (x >= 1 && x <= N && y >= 1 && y <= M) {
//			cout << "At:" << x << "," << y << ",Fc=" << T << "M = " << MAP[x][y] << endl;
			x = x + F[T][1];
			y = y + F[T][0];
			if (MAP[x][y] == 1) {
//				TAG;
				return false;
			}
			if (MAP[x][y] == 2) {
				T = 3 - T;
			} else if (MAP[x][y] == 3) {
				if (T == 0) T = 2;
				else if (T == 1) T = 3;
				else if (T == 2) T = 0;
				else if (T == 3) T = 1;
			}
			if (MAP[x][y] == -1) break;
			if (MAP[x][y] == 0) AMAP[x][y] = 1;
			
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (MAP[i][j] == 0 && AMAP[i][j] != 1){
//				TAG;
				return false;
			}  
		}
	}
//	for(int i = 1;i<=N;i++){
//		for(int j = 1;j<=M;j++){
//			cout << MAP[i][j] << " ";
//		}
//		cout << endl;
//	}
//	for(int i = 1;i<=N;i++){
//		for(int j = 1;j<=M;j++){
////			cout << AMAP[i][j];
//			if(MAP[i][j] != 1) cout << S[i][j-1];
//			else cout << (ANSS[i][j] ? '|' : '-');
//		}
//		cout << endl;
//	}
//	cout << endl;
	return true;
}

int siz;
bool fnd;

void dfs(int k) {
	if(fnd) return;
//	for(auto i : P){
//		cout << i.x << " " << i.y << " " << i.fc << endl;
//	}
	if (k == siz) {
		if (test()) {
			cout << "POSSIBLE" << endl;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (MAP[i][j] != 1) cout << S[i][j - 1];
					else cout << (ANSS[i][j] ? '|' : '-');
				}
				cout << endl;
			}
			
			fnd = true;
		}
		return;
	}
	ANSS[P[k].x][P[k].y] = 0;
	dfs(k + 1);
	ANSS[P[k].x][P[k].y] = 2;
	P[k] = Point(P[k].x,P[k].y,2);
//	cout << P[k].fc << endl;
	dfs(k + 1);
}

int main() {
	FO("battery");
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		memset(S,0,sizeof(S));
		memset(MAP,0,sizeof(MAP));
		memset(ANSS,0,sizeof(ANSS));
		memset(AMAP,0,sizeof(AMAP));
		P.clear();
		cin >> N >> M;
		for (int i = 1; i <= N; i++) {
			cin >> (S[i]);
//			cout << S[i];
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				MAP[i][j] = chk(S[i][j - 1]);
				if (MAP[i][j] == 1) P.push_back(Point(i, j, 0));
			}
		}
		fnd = false;
//		for (int i = 1; i <= N; i++) {
//			for (int j = 1; j <= M; j++) {
//				cout << MAP[i][j] << " ";
//			}
//			cout << endl;
//		}
		siz = P.size();
//		cout << siz << endl;
		dfs(0);
		if(!fnd) cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
