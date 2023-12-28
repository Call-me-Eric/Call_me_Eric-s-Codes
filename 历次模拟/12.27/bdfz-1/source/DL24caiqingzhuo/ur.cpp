#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1e3;
int n, k, p;
bitset <N> b;

struct node
{
	int l1;
	int l2;
	int num;
};

bool cmp(node i, node j)
{
	return i.num > j.num;
}

vector <node> w;

void output(node s)
{
	int l1 = s.l1, l2 = s.l2;
	for(int i = 1; i <= p / l1; i = i + 1)
		for(int j = 1; j <= l1; j = j + 1)
			putchar(j <= l2 ? '1' : '0');
}

signed main() 
{
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	cin >> n >> k;
	p = n;
	for(int i = 2; i <= n; i = i + 1)
	{
		while(n % i == 0)
		{
			n /= i;
			if(!b[i])
			{
				b[i] = 1;
				for(int j = i; j <= k; j = j + i)
					w.push_back((node){p / i, j / i, j});
			}
		}
	}
	sort(w.begin(), w.end(), cmp);
	if(w.size())
	{
//		cout << w[0].l1 << " " << w[0].l2 << " " << w[0].num << "\n";
		output(w[0]);
	}
	else
		for(int i = 1; i <= p; i = i + 1)
			putchar('0');
	return 0;
}
