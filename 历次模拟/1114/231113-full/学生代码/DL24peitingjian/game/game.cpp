#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N = 200010;

int n;
int L, R;
int a[N], b[N];
bool success;

bool cmp(int a, int b)
{
	return a > b;
}

signed main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	cin >> n >> L >> R;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	// 如果要超出
	int sum = 0;
	memcpy(b, a, sizeof a);
	sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; i ++ ) if (i & 1) sum += b[i];
	if (sum > R || sum < L) success = true; 
	// 如果要低于
	sum = 0;
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i ++ ) if (i & 1) sum += b[i];
	if (sum > R || sum < L) success = true;
	
	if (success) cout << "Alice" << '\n';
	else cout << "Bob" << '\n';
	return 0;
}
/*
5
1 10
1 1 1 1 1
*/
