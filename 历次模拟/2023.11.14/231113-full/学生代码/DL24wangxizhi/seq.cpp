#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int>pii;
const int maxn=3e5+10;
int n,Q,a[maxn],ans[maxn];
vector<pii>bucr[maxn];
int fir[maxn],lst[maxn];



namespace subtask2
{
	struct mytype
	{
		int l,r,cur;
		friend bool operator < (const mytype&A,const mytype&B){return A.l<B.l;}
	};
	set<mytype>s;
	
	struct segmenttree
	{
		#define ls (p<<1)
		#define rs (p<<1|1)
		#define mid ((t[p].l+t[p].r)>>1)
		struct node{int l,r,val,tag;}t[maxn<<2];
		inline void pushup(int p){t[p].val=t[ls].val+t[rs].val;}
		inline void updata(int p,int x){t[p].val+=(t[p].r-t[p].l+1)*x,t[p].tag+=x;}
		inline void pushdown(int p){if(t[p].tag) updata(ls,t[p].tag),updata(rs,t[p].tag),t[p].tag=0;}
		inline void build(int p,int l,int r)
		{
			t[p]={l,r,0,0};
			if(l==r) return;
			build(ls,l,mid),build(rs,mid+1,r);
		}
		inline void modify(int p,int l,int r,int x)
		{
			if(l<=t[p].l && t[p].r<=r) return updata(p,x);
			pushdown(p);
			if(l<=mid) modify(ls,l,r,x);
			if(r>mid) modify(rs,l,r,x);
			pushup(p); 
		}
		inline int qsum(int p,int l,int r)
		{
			if(l<=t[p].l && t[p].r<=r) return t[p].val;
			pushdown(p);
			if(r<=mid) return qsum(ls,l,r);
			if(l>mid) return qsum(rs,l,r);
			return qsum(ls,l,r)+qsum(rs,l,r); 
		}
	}tr;
	inline void solve()
	{
		tr.build(1,1,n);
		for(int i=1;i<=n;i++)
		{
			if(lst[a[i]]==i)
			{
				int R=fir[a[i]];
				if(s.empty()) s.insert({1,R,a[i]});
				else
				{
					int L=(prev(s.end())->r)+1;
					vector<mytype>del;
					for(auto seg:s)
					{
						if(seg.l>R) break;
						if(seg.cur>=a[i]) continue;
						L=min(L,seg.l);
						del.push_back(seg);
						if(seg.r>R){s.insert({R+1,seg.r,seg.cur}); break;}
					}
					for(auto seg:del) s.erase(seg);
					if(L<=R) s.insert({L,R,a[i]});
				}
			}
			for(auto seg:s) tr.modify(1,seg.l,seg.r,seg.cur);
			for(auto qs:bucr[i]) ans[qs.second]=tr.qsum(1,qs.first,i);
		}
		for(int i=1;i<=Q;i++) cout<<ans[i]<<'\n';
	}
}


namespace subtask1
{
	int cur[maxn],val[maxn];
	struct BIT
	{
		int c[maxn];
		inline int lowbit(int x){return x&(-x);}
		inline void add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
		inline int qsum(int x){int re=0;for(;x;x-=lowbit(x))re+=c[x];return re;} 
	}tr;
	inline void solve()
	{
		for(int i=1;i<=n;i++)
		{
			if(lst[a[i]]==i)
				for(int j=1;j<=fir[a[i]];j++)
					cur[j]=max(cur[j],a[i]);
			for(int j=1;j<=n;j++)
			{
				if(!cur[j]) break;
				tr.add(j,cur[j]);
			}
			for(auto qs:bucr[i]) ans[qs.second]=tr.qsum(i)-tr.qsum(qs.first-1);
		}
		for(int i=1;i<=Q;i++) cout<<ans[i]<<'\n';
	}
}
inline void solve()
{
	cin>>n>>Q,fill(fir+1,fir+n+1,n+1);
	for(int i=1;i<=n;i++) cin>>a[i],lst[a[i]]=i,fir[a[i]]=min(fir[a[i]],i);
	for(int i=1,l,r;i<=Q;i++) cin>>l>>r,bucr[r].push_back({l,i});
	if(n<=3000) subtask1::solve();
	else subtask2::solve();	
}
signed main()
{
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
