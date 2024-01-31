#include <bits/stdc++.h>

using namespace std;

inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int main() {
	int t = read(), n, k, ans, i, j;
	map<int, int> m, c;
	while (t--) {
		n = read(), k = read(), ans = 0, m.clear(), c.clear();
		while (n--)
			++m[read()];
		for (i = 0, j = 0; m.size() && (i < k || m[j]); m.erase(j++))
			if (!m[j] && i < k)
				++i;
		m.erase(j);
		ans = m.size();
		for (auto ii : m)
			++c[ii.second];
		for (auto ii : c)
			if (ii.first <= k)
				j = min(ii.second, k / ii.first), ans -= j, k -= j * ii.first;
			else
				break;
        printf("%d\n",ans);
	}
	return 0;
}
