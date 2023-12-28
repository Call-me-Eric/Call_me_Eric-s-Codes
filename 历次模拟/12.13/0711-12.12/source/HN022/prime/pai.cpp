#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i+=1)
#define per(i, x, y) for (int i = (x); i >= (y); i-=1)
#define epr(i, x) for (int i = head[x]; i; i = nxt[i])
#define fi first
#define se second
#define ep emplace
#define eb emplace_back

using namespace std;

typedef long long LL;
typedef pair <int, int> PII;

template <typename T>
inline T gi()
{
	T x = 0, f = 0; char c = getchar();
	while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return f ? -x : x;
}

const int N = 100003;

mt19937 rnd(random_device{}());

int main()
{
	//freopen(".in", "r", stdin);
	for (int i = 1; i <= 100000; i+=1)
	{
		system("./data"); system("./bf"); system("./prime");
		printf("Case #%d: ", i);
		if (system("diff prime.out prime.ans -w")) {puts("WA"); return 0;}
		puts("AC");
	}
	return !!0;
}
