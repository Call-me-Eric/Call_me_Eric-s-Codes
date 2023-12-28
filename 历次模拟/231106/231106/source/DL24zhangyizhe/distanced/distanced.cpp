# include <bits/stdc++.h>

using namespace std;

# define ll long long
# define PII pair< int , int >
# define MP make_pair
# define fi first
# define se second
# define pb push_back

int read()
{
# define C ch = getchar()
	int x = 0 , f = 1; char C;
	for(; ch > '9' || ch < '0'; C) if(ch == '-') f = -1; for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x * f;
}

const int N = 1e5 + 5;
int n , t;
ll s[N] , mx[N];

struct node
{
	int x;
	ll a;
	node() {}
	node(int x , ll a) : x(x) , a(a) {}
	bool operator < (const node &rhs) const {return x < rhs.x;}
} c[N] , sta[N];

bool link(node x , node y) {return y.x - x.x <= t;}

int top , vis[N] , p;

struct seg
{
	ll v;
	int l , r;
	seg() {}
	seg(ll v , int l , int r) : v(v) , l(l) , r(r) {}
	bool operator < (const seg &rhs) const {return v < rhs.v;}
} ;
priority_queue< seg > Q;

struct DSU
{
	int fa[N];
	void init() {for(int i = 1; i <= top; i++) fa[i] = i;}
	void Merge(int l , int r)
	{
		for(int i = l; i <= r; i++) fa[i] = fa[i - 1];
		ll res = 0;
		for(int i = l; i <= r; i++)
		{
			if(sta[i].a <= 0) res += sta[i].a;
			else if(res < 0) Q.push(seg(-res , 0 , 0)) , res = 0; 
		}
		if(res < 0) Q.push(seg(-res , 0 , 0));
	}
} F;

struct ST_Table
{
	int f[N][20];
	void init()
	{
		for(int i = 1; i <= top; i++) f[i][0] = i;
		for(int j = 1; (1 << j) <= top; j++)
		{
			for(int i = 1; i + (1 << j - 1) <= top; i++)
			{
				if(s[f[i][j - 1]] > s[f[i + (1 << j - 1)][j - 1]]) f[i][j] = f[i][j - 1];
				else f[i][j] = f[i + (1 << j - 1)][j - 1];
			}
		}
	}
	int Query(int l , int r)
	{
		int t = __lg(r - l + 1);
		if(s[f[l][t]] > s[f[r - (1 << t) + 1][t]]) return f[l][t];
		return f[r - (1 << t) + 1][t];
	}
} st;

int main()
{
	freopen("distanced.in" , "r" , stdin);
	freopen("distanced.out" , "w" , stdout);
	n = read() , t = read();
	for(int i = 1; i <= n; i++) c[i].x = read();
	for(int i = 1; i <= n; i++) c[i].a = read();
	sort(c + 1 , c + n + 1);
	for(int i = 1; i <= n; i++)
	{
		if(c[i].a >= 0) sta[++top] = c[i];
		else if(!link(c[i - 1] , c[i + 1]) && link(c[i - 1] , c[i]) && link(c[i] , c[i + 1])) sta[++top] = c[i];
	}
	for(int i = 1; i <= top; i++) s[i] = s[i - 1] + sta[i].a;
	st.init();
	sta[0].x = -2e9 , sta[0].a = -1;
	for(int i = top; i >= 1; i--)
	{
		if(s[i] > s[p]) p = i;
		if(sta[i].a >= 0 && sta[i - 1].a < 0 || !link(sta[i - 1] , sta[i])) Q.push(seg(s[p] - s[i - 1] , i , p));
		if(!link(sta[i - 1] , sta[i])) vis[i] = 1 ,  p = 0;
	}
	F.init();
	for(int i = 1; i <= n; i++)
	{
		while(!Q.empty())
		{
			seg u = Q.top(); Q.pop();
			if(u.l == 0 && u.r == 0) {mx[i] = mx[i - 1] + u.v; break ;}
			else
			{
				if(F.fa[u.l] != u.l) continue ;
				if(F.fa[u.r] != u.r) 
				{
					p = st.Query(u.l , F.fa[u.r] - 1);
					Q.push(seg(s[p] - s[u.l - 1] , u.l , p));
				}
				else
				{
					mx[i] = mx[i - 1] + u.v;
					F.Merge(u.l , u.r);
					break ;
				}
			}
		}
		mx[i] = max(mx[i] , mx[i - 1]);
	}
	for(int i = 1; i <= n; i++) cout << mx[i] << ' ';
	return 0;
}
