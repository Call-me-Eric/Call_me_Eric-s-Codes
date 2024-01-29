#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	long long xr = 0, F = 1;
	char cr;
	while (cr = getchar(), cr < '0' || cr > '9')
		if (cr == '-')
			F = -1;
	while (cr >= '0' && cr <= '9') xr = (xr << 3) + (xr << 1) + (cr ^ 48), cr = getchar();
	return xr * F;
}

char wr[20];
inline void write(int x)
{
	if(x == 0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int i = 1;
	while(x)
	{
		wr[i] = x % 10 + '0';
		x /= 10;
		i ++;
	}
	i --;
	while(i)
	{
		putchar(wr[i]);
		i --;
	}
	putchar('\n');
}

bool gr(int i, int j)
{
	return i > j;
}

const int N = 214514;
int n, q;
vector <int> l[N], r[N];

struct query
{
	int l;
	int r;
	int id;
};

query a[N];

const int len = 400;

int get(int x) { return x / len; }

bool cmp(query i, query j)
{
	if(get(i.l) != get(j.l))
		return get(i.l) < get(j.l);
	else
	{
		if(get(i.l) & 1)
			return i.r < j.r;
		else
			return i.r > j.r;
	}
}

int ans[N], sum;

void addlef(int lef, int rig)
{
	if(lef >= rig)
		return;
	if(l[lef].size() == 0)
		return;
	int L = -1, R = l[lef].size();
	while(L < R - 1)
	{
		int mid = (L + R) / 2;
		if(l[lef][mid] <= rig)
			L = mid;
		else
			R = mid;
	}
	sum += L + 1;
}

void dellef(int lef, int rig)
{
	if(lef >= rig)
		return;
	if(l[lef].size() == 0)
		return;
	int L = -1, R = l[lef].size();
	while(L < R - 1)
	{
		int mid = (L + R) / 2;
		if(l[lef][mid] <= rig)
			L = mid;
		else
			R = mid;
	}
	sum -= L + 1;
}

void addrig(int lef, int rig)
{
	if(lef >= rig)
		return;
	if(r[rig].size() == 0)
		return;
	int L = -1, R = r[rig].size();
	while(L < R - 1)
	{
		int mid = (L + R) / 2;
		if(r[rig][mid] >= lef)
		{
//			cout << mid << r[rig][mid] << " ?\n";
			L = mid;
		}
		else
		{
//			cout << mid << r[rig][mid] << " !\n";
			R = mid;
		}
	}
	sum += L + 1;
}

void delrig(int lef, int rig)
{
	if(lef >= rig)
		return;
	if(r[rig].size() == 0)
		return;
	int L = -1, R = r[rig].size();
	while(L < R - 1)
	{
		int mid = (L + R) / 2;
		if(r[rig][mid] >= lef)
			L = mid;
		else
			R = mid;
	}
	sum -= L + 1;
}

signed main()
{
	freopen("lct.in", "r", stdin);
	freopen("lct.out", "w", stdout); 
	n = read();
	q = read();
	for(int i = 1; i <= n - 1; i = i + 1)
	{
		int L, R;
		L = read();
		R = read();
		if(L > R)
			swap(L, R);
		l[L].push_back(R);
		r[R].push_back(L);
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		if(l[i].size() > 1)
			sort(l[i].begin(), l[i].end());
		if(r[i].size() > 1)
			sort(r[i].begin(), r[i].end(), gr);
//		for(int j = 0; j < l[i].size(); j = j + 1)
//			cout << l[i][j] << " ";
//		cout << "\n";
//		for(int j = 0; j < r[i].size(); j = j + 1)
//			cout << r[i][j] << " ";
//		cout << "\n\n";
	}
	for(int i = 1; i <= q; i = i + 1)
	{
		a[i].id = i;
		a[i].l = read();
		a[i].r = read();
	}
	sort(a + 1, a + 1 + q, cmp);
	int lef = 1, rig = 1;
	for(int i = 1; i <= q; i = i + 1)
	{
		while(lef < a[i].l)
		{
			dellef(lef, rig);
			lef ++;
		}
//		cout << a[i].l << " " << a[i].r << " " << sum << "\n";
		while(lef > a[i].l)
		{
			lef --;
			addlef(lef, rig);
		}
//		cout << a[i].l << " " << a[i].r << " " << sum << "\n";
		while(rig < a[i].r)
		{
			rig ++;
			addrig(lef, rig);
		}
//		cout << a[i].l << " " << a[i].r << " " << sum << "\n";
		while(rig > a[i].r)
		{
			delrig(lef, rig);
			rig --;
		}
//		cout << a[i].l << " " << a[i].r << " " << sum << "\n\n";
		ans[a[i].id] = a[i].r - a[i].l + 1 - sum;
	}
	for(int i = 1; i <= q; i = i + 1)
		write(ans[i]);
	return 0;
}
