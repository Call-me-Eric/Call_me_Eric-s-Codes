# include <bits/stdc++.h>

using namespace std;

# define ll long long

int read()
{
# define C ch = getchar()
	int x = 0; char C;
	for(; ch > '9' || ch < '0'; C); for(; ch >= '0' && ch <= '9'; C) x = (x << 3) + (x << 1) + (ch ^ 48);
	return x;
}

const int N = 3e5 + 5;
int n , q , a[N] , fir[N] , lst[N];
ll ans[N];

namespace subtask1
{
	const int N1 = 3e3 + 5;
	ll f[N1][N1];
	int g[N1][N1];
	bool solve()
	{
		if(n > 3000) return 0;
		for(int l = 1; l <= n; l++)
		{
			for(int r = l; r <= n; r++)
			{
				if(fir[a[r]] >= l && lst[a[r]] <= r) g[l][r] = max(g[l][r - 1] , a[r]);
				else g[l][r] = g[l][r - 1];
				f[l][r] = f[l][r - 1] + g[l][r];
			}
		}
		for(int i = 1 , l , r; i <= q; i++)
		{
			l = read() , r = read();
			ll ans = 0;
			for(int j = l; j <= r; j++) ans += f[j][r];
			printf("%lld\n" , ans);
		}
		return 1;
	}
}

struct Ask
{
	int l , id;
	Ask() {}
	Ask(int l , int id) : l(l) , id(id) {}
} ;
vector< Ask > v[N];

struct node
{
	ll s , c;
	node() {}
	node(ll s , ll c) : s(s) , c(c) {}
	node operator + (const node &rhs) {return node(s + rhs.s , c + rhs.c);}
} ;

struct Tag
{
	ll addx , addc , cx;
	Tag() {}
	Tag(ll addx , ll addc , ll cx) : addx(addx) , addc(addc) , cx(cx) {} 
} ;

struct Seg
{
	node tr[N<<2];
	Tag tag[N<<2];
# define lc x << 1
# define rc x << 1 | 1
# define mid (l + r >> 1)
	void PushUp(int x) {tr[x] = tr[lc] + tr[rc];}
	void Addx(int x , int l , int r , ll v)
	{
		tr[x].s += v * tr[x].c;
		if(tag[x].cx) tag[x].addc += tag[x].cx * v;
		else tag[x].addx += v; 
	}
	void Addc(int x , int l , int r , ll v)
	{
		tr[x].s += (r - l + 1) * v;
		tag[x].addc += v;
	}
	void Cx(int x , int l , int r , ll v)
	{
		tr[x].c += (r - l + 1) * v;
		tag[x].cx = v;
	}
	void PushDown(int x , int l , int r)
	{
		if(tag[x].addx) Addx(lc , l , mid , tag[x].addx) , Addx(rc , mid + 1 , r , tag[x].addx);
		if(tag[x].addc) Addc(lc , l , mid , tag[x].addc) , Addc(rc , mid + 1 , r , tag[x].addc);
		if(tag[x].cx) Cx(lc , l , mid , tag[x].cx) , Cx(rc , mid + 1 , r , tag[x].cx);
		tag[x] = Tag(0 , 0 , 0);
	}
	void Upt(int x , int l , int r , int L , int R , int v , int opt)
	{
		if(L <= l && r <= R)
		{
//			cout << l << ' ' << r << ' ' << v << ' ' << opt << '*' << endl;
			if(opt) Addx(x , l , r , v);
			else Cx(x , l , r , v);
			return ;
		}
		PushDown(x , l , r);
		if(mid >= L) Upt(lc , l , mid , L , R , v , opt);
		if(mid < R) Upt(rc , mid + 1 , r , L , R , v , opt);
		PushUp(x);
	}
	int Query(int x , int l , int r , int L , int R)
	{
		if(L <= l && r <= R) return tr[x].s;
		PushDown(x , l , r);
		ll res = 0;
		if(mid >= L) res += Query(lc , l , mid , L , R);
		if(mid < R) res += Query(rc , mid + 1 , r , L , R);
		return res; 
	}
} tr;

struct data
{
	int v , l , r;
	data() {}
	data(int v , int l , int r) : v(v) , l(l) , r(r) {}
	bool operator < (const data &rhs) const {return v > rhs.v;}
} ;
set< data > S;

int main()
{
	freopen("seq.in" , "r" , stdin);
	freopen("seq.out" , "w" , stdout);
	n = read() , q = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) if(!fir[a[i]]) fir[a[i]] = i;
	for(int i = n; i; i--) if(!lst[a[i]]) lst[a[i]] = i;
	if(subtask1::solve()) return 0;
	for(int i = 1 , l , r; i <= q; i++) l = read() , r = read() , v[r].push_back(Ask(l , i));
	S.insert(data(0 , 1 , n));
	for(int i = 1 , L , R , flag = 0; i <= n; i++)
	{
		if(lst[a[i]] <= i)
		{
//			cout << i << ' ' << a[i] << endl;
			auto it = S.lower_bound(data(a[i] , 1 , fir[a[i]]));
			if(it == S.begin()) L = 1;
			else L = prev(it)->r + 1; 
			if(L <= fir[a[i]])
			{
				while((*it).l <= fir[a[i]] && (*it).r <= fir[a[i]] && it->v && it != S.end()) it++ , S.erase(prev(it));
				R = fir[a[i]];
				S.insert(data(a[i] , L , R));
//				cout << L << ' ' << R << '*' << endl;
				int v = it->v , r = it->r;
				S.erase(it);
				S.insert(data(v , R + 1 , r));
				tr.Upt(1 , 1 , n , L , R , a[i] , 0) , flag = 1;
//				for(it = S.begin(); it != S.end(); it++)
//				{
//					cout << it->v << ' ' << it->l << ' ' << it->r << endl;
//				}
			}
		}
		tr.Upt(1 , 1 , n , 1 , i , 1 , 1);
//		for(int j = 1; j <= i; j++)
//		{
//			cout << j << ' ' << i << ' ' << subtask1::f[j][i] << ' ' << tr.Query(1 , 1 , n , j , j) << endl;
//		}
		for(auto t : v[i]) ans[t.id] = tr.Query(1 , 1 , n , t.l , i);
	}
	for(int i = 1; i <= q; i++) printf("%lld\n" , ans[i]);
	return 0;
}
