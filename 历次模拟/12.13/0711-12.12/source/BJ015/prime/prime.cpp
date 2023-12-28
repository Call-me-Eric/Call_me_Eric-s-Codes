# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
# define fi first
# define se second
bool isprime(ll x){
	if (x == 1) return false;
	for (ll i = 2; i * i <= x; i++) if (x % i == 0) return false;
	return true;
}
const int MAXS = 110;
int p[26] = {2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
ll pw[12] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000};
int pt[26];
int pt1[MAXS][26];
int pts[MAXS][26];
vector<pii> adj[MAXS];
ull gethsh(){
	ull ans = 0, bs = 19260817;
	for (int j = 0; j < 26; j++){
		ans = ans * bs + (ull)(pt[j]);
	}
	return ans;
}
int cnt;
map<ull, int> mp;
void dfs(int ps, ll nm){
	if (mp.find(gethsh()) != mp.end()) return;
	mp[gethsh()] = ++cnt;
	int nw = cnt;
	memcpy(pts[cnt], pt, sizeof(pt));
	// if ((++cnt) % 100000 == 0) cerr << "cnt " << cnt << '\n';
	memcpy(pt1[ps], pt, sizeof(pt));
	for (int i = 0; i <= 9; i++){
		bool flg = true;
		for (int j = 0; j < 26; j++){
			if (i == (p[j] / pw[pt[j]]) % 10) pt[j]++;
			if (pw[pt[j]] > p[j]) flg = false;
		}
		if (flg){
			dfs(ps + 1, nm + pw[ps] * i);
			adj[nw].push_back(pii(i, mp[gethsh()]));
			// cerr << "t " << nw << ' ' << i << ' ' << t[nw][i] << '\n';
		}
		memcpy(pt, pt1[ps], sizeof(pt));
	}
}
const int MAXN = 100051;
const int P = 998244353;
int T;
int f[MAXN][110][2][2];
char str[MAXN];
int len1, len2;
int l[MAXN], r[MAXN];
int a[] = {0, 1, 4, 6, 8, 9};
void upd(int &a, int b){
	a = (a + b > P) ? a + b - P : a + b;
}
int main(){
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	dfs(0, 0);
	cin >> T;
	while (T--){
		cin >> (str + 1);
		len1 = strlen(str + 1);
		for (int i = 1; i <= len1; i++) l[i] = str[len1 - i + 1] - '0';
		cin >> (str + 1);
		len2 = strlen(str + 1);
		for (int i = 1; i <= len2; i++) r[i] = str[len2 - i + 1] - '0';
		for (int i = 0; i <= len2; i++){
			for (int s = 1; s <= cnt; s++){
				f[i][s][0][0] = f[i][s][0][1] = f[i][s][1][0] = f[i][s][1][1] = 0;
			}
		}
		f[0][1][1][1] = 1;
		for (int i = 0; i <= len2 - 1; i++){
			for (int s = 1; s <= cnt; s++){
				int u, v;
				// cerr << "f " << i << ' ' << s << ' ' << u << ' ' << v << ' ' << f[i][s][u][v] << '\n';
				for (pii j : adj[s]){
					u = 0; v = 0;
					int nm = j.fi, s1 = j.se;
					bool u1 = nm > l[i + 1] || (nm == l[i + 1] && u);
					bool v1 = nm < r[i + 1] || (nm == r[i + 1] && v);
					upd(f[i + 1][s1][u1][v1], f[i][s][u][v]);
					
					u = 0; v = 1;
					u1 = nm > l[i + 1] || (nm == l[i + 1] && u);
					v1 = nm < r[i + 1] || (nm == r[i + 1] && v);
					upd(f[i + 1][s1][u1][v1], f[i][s][u][v]);
					
					u = 1; v = 0;
					u1 = nm > l[i + 1] || (nm == l[i + 1] && u);
					v1 = nm < r[i + 1] || (nm == r[i + 1] && v);
					upd(f[i + 1][s1][u1][v1], f[i][s][u][v]);
					
					u = 1; v = 1;
					u1 = nm > l[i + 1] || (nm == l[i + 1] && u);
					v1 = nm < r[i + 1] || (nm == r[i + 1] && v);
					upd(f[i + 1][s1][u1][v1], f[i][s][u][v]);
				}
			}
		}
		int ans = 0;
		for (int s = 1; s <= cnt; s++){
			upd(ans, f[len2][s][1][1]);
		}
		cout << ans << '\n';
	}
	return 0;
}
