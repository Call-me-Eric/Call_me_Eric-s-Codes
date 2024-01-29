#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	#endif
}

const int mod=998244353;
inline int qmo(int x){return x+((x>>31)&mod);}
inline int add(int x,int y){return qmo(x+y-mod);}
inline int sub(int x,int y){return qmo(x-y);}
inline void inc(int &x,int y){x=add(x,y);}
inline void dec(int &x,int y){x=sub(x,y);}
inline int quick_pow(int x,int k){int res=1; for (;k;k>>=1,x=1ll*x*x%mod) if (k&1) res=1ll*res*x%mod; return res;}

const int N=710;

int n,q;
struct eq
{
	vector<int> a[N];
	int cnt;
	bool gg;
	void init(int size)
	{
		rep(i,0,size-1) a[i].resize(size+1);
		gg=0,cnt=0;
	}
	void gauss(vector<int> &X)
	{
		if (gg) return;
		rep(i,0,n-1) if (X[i])
		{
			if (!a[i][i])
			{
				int iv=quick_pow(X[i],mod-2);
				rep(j,i,n) X[j]=1ll*X[j]*iv%mod;
				a[i]=X;
				cnt++;
				rep(j,i+1,n-1) if (a[i][j]&&a[j][j])
				{
					int coef=a[i][j];
					rep(k,j,n) dec(a[i][k],1ll*coef*a[j][k]%mod);
				}
				rep(j,0,i-1) if (a[j][i])
				{
					int coef=a[j][i];
					rep(k,i,n) dec(a[j][k],1ll*coef*a[i][k]%mod);
				}
				return;
			}
			else
			{
				int coef=X[i];
				if (coef) rep(j,i,n) dec(X[j],1ll*a[i][j]*coef%mod);
			}
		}
		if (X[n])
		{
			gg=1;
			return;
		}
	}
	int val()
	{
		if (gg) return -1;
		if (cnt<n) return 0;
		return 1;
	}
	vector<int> getx()
	{
		vector<int> hh(n);
		rep(i,0,n-1) hh[i]=a[i][n];
		return hh;
	}
	void clear()
	{
		a.clear();
		a.shrink_to_fit();
	}
};

int lst[N];
vector<int> vec[N];

#define mid ((start+end)>>1)
vector<vector<int> > ve[N<<2];
void insert(int node,int start,int end,int L,int R,const vector<int> &e)
{
	if (start>=L&&end<=R)
	{
		ve[node].push_back(e);
		return;
	}
	if (L<=mid) insert(node<<1,start,mid,L,R,e);
	if (R>mid) insert(node<<1|1,mid+1,end,L,R,e);
}

int ans[N];
vector<int> a2[N];
void solve(int node,int start,int end,eq &e)
{
	static mt19937 rng(114514);
	shuffle(ve[node].begin(),ve[node].end(),rng);
	for (auto t:ve[node]) e.gauss(t);
	// printf("start %d end %d e :\n",start,end);
	// printf("gg %d cnt %d\n",e.gg,e.cnt);
	// rep(i,0,n-1) 
	// {
	// 	rep(j,0,n) printf("%d ",e.a[i][j]);
	// 	printf("\n");
	// }
	// printf("\n");
	if (e.gg)
	{
		rep(i,start,end) ans[i]=-1;
		return;
	}
	if (start==end)
	{
		ans[start]=e.val();

		if (ans[start]==1) 
		{
			a2[start]=e.getx();
		}
		return;
	}
	eq r=e;
	solve(node<<1,start,mid,e);
	solve(node<<1|1,mid+1,end,r);
	e.clear();
	r.clear();
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	cin>>n>>q;
	rep(i,1,n)
	{
		vec[i].resize(n+1);
		rep(j,0,n) cin>>vec[i][j];
	}
	rep(i,1,q)
	{
		int id; cin>>id;
		insert(1,0,q,lst[id],i-1,vec[id]);
		lst[id]=i;
		rep(j,0,n) cin>>vec[id][j];
	}
	rep(i,1,n) insert(1,0,q,lst[i],q,vec[i]);

	eq tmp; tmp.init(n);
	solve(1,0,q,tmp);

	rep(i,0,q)
	{
		if (ans[i]==-1) printf("No\n");
		if (ans[i]==0) printf("Many\n");
		if (ans[i]==1)
		{
			rep(j,0,n-1) printf("%d ",a2[i][j]);
			printf("\n");
		}
	}

	return 0;
}