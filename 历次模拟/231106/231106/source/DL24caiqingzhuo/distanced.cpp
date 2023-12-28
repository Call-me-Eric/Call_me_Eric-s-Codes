#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 114514;
const int N70 = 2114;
int n, t;
int lst;
int maxn[N70];
int ans[N70];

bool ff = true;

struct car
{
	int mei;
	int pos;
};
car c[N];

int f[N70][N70];

bool cmp(car i, car j)
{
	return i.pos < j.pos;
}

struct dq
{
	int t[N70];
	int f, b;
	void init()
	{
		f = 2;
		b = 1;
	}
	bool empty()
	{
		return f >= b + 1;
	}
	int front()
	{
		return t[f];
	}
	int back()
	{
		return t[b];
	}
	void pop_front()
	{
		f ++;
	}
	void push_back(int x)
	{
		b ++;
		t[b] = x;
	}
};
dq q[N70];

signed main()
{
	freopen("distanced.in", "r", stdin);
	freopen("distanced.out", "w", stdout);
	cin >> n >> t;
	for(int i = 1; i <= n; i = i + 1)
		cin >> c[i].pos;
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i].mei;
		if(c[i].mei < 0)
			ff = false;
	}
	sort(c + 1, c + 1 + n, cmp);
	if(ff)
	{
		priority_queue <int> p;
		int sum = c[1].mei;
		for(int i = 2; i <= n; i = i + 1)
		{
			if(c[i].pos - c[i - 1].pos > t)
			{
				p.push(sum);
				sum = c[i].mei;
			}
			else
				sum += c[i].mei;
		}
		p.push(sum);
		int all = 0;
		for(int i = 1; i <= n; i = i + 1)
		{
			if(!p.empty())
			{
				all += p.top();
				p.pop();
			}
			cout << all << " ";
		}
		return 0;
	}
	f[1][1] = c[1].mei;
	for(int i = 1; i <= n; i = i + 1)
	{
		q[i].init();
		q[i].push_back(1);
	}
	for(int i = 2; i <= n; i = i + 1)
	{
		int l = 0, r = i;
		while(l < r - 1)
		{
			int mid = (l + r) / 2;
			if(c[i].pos - c[mid].pos > t)
				l = mid;
			else
				r = mid;
		}
//		cout << i << " " << lst << " " << l << "\n";
		for(int j = 1; j <= i; j = j + 1)
			for(int k = lst + 1; k <= l; k = k + 1)
				maxn[j] = max(maxn[j], f[k][j]);
		lst = l;
		for(int j = 1; j <= i; j = j + 1)
		{
			while(!q[j].empty() && q[j].front() <= l)
				q[j].pop_front();
			f[i][j] = max(maxn[j - 1], f[q[j].front()][j]) + c[i].mei;
			q[j].push_back(i);
			while(f[q[j].front()][j] < f[q[j].back()][j])
				q[j].pop_front();
			ans[j] = max(ans[j], f[i][j]);
		}
	}
//	for(int i = 1; i <= n; i = i + 1)
//	{
//		for(int j = 1; j <= n; j = j + 1)
//			cout << f[i][j] << " ";
//		cout << "\n";
//	}
	for(int i = 1; i <= n; i = i + 1)
		ans[i] = max(ans[i], ans[i - 1]),
		cout << ans[i] << " ";
	return 0;
}
