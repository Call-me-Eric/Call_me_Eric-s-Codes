#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, x, y) for(int i = (x), stOzzh = (y); i <= stOzzh; ++i)
#define irep(i, x, y) for(int i = (x), stOzzh = (y); i >= stOzzh; --i)
#define pb emplace_back
#define il inline
#define fi first
#define se second
#define let const auto
#define all(s) s.begin(), s.end()
using pii = pair<int, int>;
using vint = vector<int>;
mt19937_64 rnd(time(0));
ll ksm(ll x, ll y, ll P) {
	ll res = 1;
	for(; y; y >>= 1, x = __int128(x) * x % P) if(y & 1) res = __int128(res) * x % P;
	return res;
}
const int test_time = 8;
bool millor_rabin(ll n) {
	if(n < 3 || n % 2 == 0) return n == 2;
	ll u = n - 1;
	int t = 0;
	while(u & 1 ^ 1) u >>= 1, t++;
	rep(tim, 1, test_time) {
		int a = rnd() % (n - 2) + 2, v = ksm(a, u, n);
		if(v == 1) continue;
		int s;
		for(s = 0; s < t; ++s) {
			if(v == n - 1) break;
			v = (__int128)v * v % n;
		}
		if(s == t) return 0;
	}
	return 1;
}
vint vec = {0, 1, 4, 6, 8, 9};
set<string> sets;
void expand(string s) {
	int len = s.length();
	for(int x : vec)
		rep(i, 0, len) {
//			if(x != 1 && x != 9 && i == t - 1) continue;
			string t = s;
			t.insert(i, 1, x + '0');
			sets.insert(t); 
		}
}
set<string> sets2;
bool chk(string s) {
	if(millor_rabin(stoi(s.c_str()))) return false;
	rep(i, 0, s.length() - 1) {
		string t = s;
		t.erase(i, 1);
		if(sets2.find(t) == sets2.end()) return false;
	}
	return true;
}
set<ll> lst;
signed main() {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	sets2;
	sets2.insert("");
	rep(i, 1, 8) {
		sets.clear();
		set<string> sets3;
		for(let t : sets2) expand(t);
		for(let t : sets) if(chk(t)) sets3.insert(t);
		sets2 = sets3;
	}
	for(let s : sets2) lst.insert(stoi(s.c_str()));
	lst.insert(1e9);
	int Q;
	cin >> Q;
	while(Q--) {
		ll l, r;
		cin >> l >> r;
		int ans = 0;
		for(int x : lst) if(x >= l && x <= r) ans++;
		cout << ans << '\n';
	}
	return 0;
}

