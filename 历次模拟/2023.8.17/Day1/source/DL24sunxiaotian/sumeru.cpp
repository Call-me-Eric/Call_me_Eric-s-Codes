#include <bits/stdc++.h>
#define ll long long
using namespace std;

int T;
ll a, b, c, d;
ll e, f, g, h;
ll i, j, k, l;

int main() {
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
	
	scanf("%d", &T);
	while (T--){
		bool flag = 1;
		scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld", &a, &e, &i, &b, &f, &j, &c, &g, &k, &d, &h, &l);
		
		if (d % max(a, max(b, c)) != 0) flag = 0;
		if (h % max(e, max(f, g)) != 0) flag = 0;
		if (l % max(i, max(j, k)) != 0) flag = 0;
		
		flag ? printf("YES\n") : printf("NO\n");
	}
	
	return 0;
}
