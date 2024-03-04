#include <bits/stdc++.h>
#define debug cout<<"fuck\n"
using namespace std;

int n, t, s;
int c[1919810];

struct p
{
	int dir;
	int zhi;
};
p z[2114514];

bool cmp(p i, p j)
{
	return i.zhi < j.zhi;
}

// 表示右端点确定时的极差 

int cnt;
int main()
{
	freopen("eliminate.in", "r", stdin);
	freopen("eliminate.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i = i + 1)
	{
		scanf("%d", &c[i]);
		for(int j = 1; j <= c[i]; j = j + 1)
		{
			scanf("%d", &t);
			cnt ++;
			z[cnt].zhi = t;
			z[cnt].dir = i;
		}
	}
//	debug;
	sort(z + 1, z + 1 + cnt, cmp);
//	for(int i = 1; i <= cnt; i = i + 1)
//		cout << z[i].zhi << "  " << z[i].dir << "\n";
//	debug;
	int l = 1, r = cnt;
	while(c[z[r].dir] > 1)
	{
		c[z[r].dir] --;
		r --;
	}
	int ans = z[r].zhi - z[l].zhi;
//	cout << l << " " << r << " " << ans << "\n";
	while(r <= cnt)
	{
		bool f = 1;
		while(c[z[l].dir] > 1)
		{
			c[z[l].dir] --;
			l ++;
			ans = min(ans, z[r].zhi - z[l].zhi);
		}
		while(c[z[l].dir] == 1)
		{
			r ++;
			c[z[r].dir] ++;
			if(r == cnt && c[z[l].dir] == 1)
			{
				f = 0;
				break;
			}
		}
		if(f == 0)
			break;
		l ++;
		ans = min(ans, z[r].zhi - z[l].zhi);
//		cout << l << " " << r << " " << ans << "\n";
	}
	cout << ans;
	return 0;
}
