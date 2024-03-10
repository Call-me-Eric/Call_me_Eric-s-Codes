#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[114][114];
int dp[114][114];
struct z {int zhi;	int cha;	bool d;};	// d == 0 zuo d == 1 you
z dp2[114][114];

void in()	{scanf("%d%d", &n, &k);	for(int i = 1; i <= n; i = i + 1)	for(int j = 1; j <= i; j = j + 1)	scanf("%d", &a[i][j]);}
void csh()	{for(int i = 1; i <= n + 1; i = i + 1)	for(int j = 0; j <= n + 1; j = j + 1)	{dp[i][j] = -114514;}	dp[1][1] = a[1][1];}
void csh2()	{for(int i = 2; i <= n + 1; i = i + 1)	for(int j = 0; j <= n + 1; j = j + 1)	{dp2[i][j].zhi = -114514;}	dp[1][1] = a[1][1];}

int d_p()
{
	int ans = -1919810;
	for(int i = 1; i <= n; i = i + 1)	for(int j = 1; j <= i; j = j + 1)	dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
	for(int i = 1; i <= n; i = i + 1)	ans = max(ans, dp[n][i]);
	return ans;
}

int s[114];
struct zb	{int x;	int y;};
zb z[114];
int q[114];

void dfs(int ceng, int dir)
{
	q[ceng] = dir;
	if(ceng == 1)				return;
	if(dp2[ceng][dir].d == 0)	dfs(ceng - 1, dir - 1);
	else						dfs(ceng - 1, dir);
}

void printq()
{
	for(int i = 1; i <= n; i = i + 1)	cout << q[i] << " ";
	cout << "\n";
}

int d___p(int ceng)
{
	int tmp = a[ceng][q[ceng]];
	a[ceng][q[ceng]] = -114514;
	int ans = -1919810;
	csh2();
	dp[1][1] = a[1][1];
	for(int i = 2; i <= n; i = i + 1)
		for(int j = 1; j <= i; j = j + 1)
		{
			dp2[i][j].cha = abs(dp2[i - 1][j].zhi - dp2[i - 1][j - 1].zhi);
			if(dp2[i - 1][j].zhi > dp2[i - 1][j - 1].zhi)	{dp2[i][j].d = 1;	dp2[i][j].zhi = dp2[i - 1][j].zhi + a[i][j];}
			else											{dp2[i][j].d = 0;	dp2[i][j].zhi = dp2[i - 1][j - 1].zhi + a[i][j];}
		}
	for(int i = 1; i <= n; i = i + 1)	if(dp2[n][i].zhi > ans)	{ans = dp2[n][i].zhi;}
//	cout << ceng << " " << q[ceng] << " " << ans << "\n";
	a[ceng][q[ceng]] = tmp;
	if(ceng == 2)	return ans;
	return max(ans, d___p(ceng - 1));
}

int d__p()
{
	int ans = -1919810;
	for(int i = 1; i <= n; i = i + 1)
		for(int j = 1; j <= i; j = j + 1)
		{
			dp2[i][j].cha = abs(dp2[i - 1][j].zhi - dp2[i - 1][j - 1].zhi);
			if(dp2[i - 1][j].zhi > dp2[i - 1][j - 1].zhi)	{dp2[i][j].d = 1;	dp2[i][j].zhi = dp2[i - 1][j].zhi + a[i][j];}
			else											{dp2[i][j].d = 0;	dp2[i][j].zhi = dp2[i - 1][j - 1].zhi + a[i][j];}
		}
	int dir = 0;
	for(int i = 1; i <= n; i = i + 1)	if(dp2[n][i].zhi > ans)	{dir = i;	ans = dp2[n][i].zhi;}
	dfs(n, dir);
//	printq();
	return d___p(n);
}

int main()
{
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	in();	// shuru
	csh();	// chushihua
	if(k == 1)	{cout << d_p();		return 0;}	// 40
	if(k == 2)	{cout << d__p();	return 0;}	// 70
	cout << "bukeyi, zongsiling" << endl;
	return 0;
}
