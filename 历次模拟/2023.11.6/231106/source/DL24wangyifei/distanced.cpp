#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
	long long xr=0,F=1; char cr;
	while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
	while(cr>='0'&&cr<='9') 
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
#define int long long
const int N=2e5+5,inf=2e15;
int n,t;
struct node {int x,w;} a[N];
il bool cmp(node x,node y) {return x.x<y.x;}
int ans[N],f[N]; 
#define pii pair<int,int>
#define fi first
#define se second
set<pii> s,mx;
void solve(int l,int r)
{
//	cout<<l<<" "<<r<<endl;
	f[l]=a[l].w;
	set<pii> S; 
	S.insert(pii(f[l],l));
	for(int i=l+1;i<=r;i++)
	{
		f[i]=-inf;
		while(S.size())
		{
			auto nw=prev(S.end());
			int st=nw->se,mx=nw->fi;
			if(a[i].x-a[st].x>t) {S.erase(nw);continue;}
			f[i]=max(f[i],mx+a[i].w);
			S.insert(pii(f[i],i));
			break;
		}
	}
	f[r]-=a[l].w+a[r].w;
	s.insert(pii(a[l].x+1,f[r])),mx.insert(pii(f[r],a[l].x+1));
}
signed main()
{
	freopen("distanced.in","r",stdin); 
	freopen("distanced.out","w",stdout); 
	n=read(),t=read();
	for(int i=1;i<=n;i++) a[i].x=read();
	for(int i=1;i<=n;i++) a[i].w=read();
	sort(a+1,a+n+1,cmp);
//	cout<<"qwq "<<endl;
	int lst=0,sum=0,st=0,cnt=0,res=0; a[0].x=-inf;
	for(int i=1;i<=n+1;i++)
	{
		if(a[i].w>=0||i>n) 
		{
			res+=a[i].w;
			if(i>n||a[i].x-a[lst].x>t) 
			{
				if(i<=n) cnt++;
				if(lst)
				{
					s.insert(pii(a[st].x,-sum)),mx.insert(pii(-sum,a[st].x));
					if(i<=n) solve(lst,i);
				}
				sum=a[i].w,lst=i,st=i;
			}
			else sum+=a[i].w,lst=i;
		}
	}
//	cout<<"done init "<<cnt<<endl;
	for(int i=cnt;i<=n;i++) ans[i]=res;
	for(int i=cnt-1;i>=1;i--)
	{
		assert(mx.size());
//		cout<<"i= "<<i<<endl;
//		for(auto x:s) cout<<x.fi<<" "<<x.se<<endl;
		int maxn=prev(mx.end())->fi,pos=prev(mx.end())->se;
//		auto qwq=mx.end(); cout<<qwq->fi<<" "<<qwq->se<<endl;
//		cout<<maxn<<" "<<pos<<endl;
		mx.erase(prev(mx.end()));
//		cout<<"pos= "<<pos<<endl;
		bool fg=0,fr=0;
		if(s.upper_bound(pii(pos-1,inf))==s.begin()) fg=1;
		auto lst=prev(s.upper_bound(pii(pos-1,inf)));
		auto nxt=s.upper_bound(pii(pos,inf));
		if(nxt==s.end()) fr=1;
		int lpos=fg?pos:lst->fi,rpos=(nxt==s.end())?0:nxt->fi;
		int lmx=fg?0:lst->se,rmx=(nxt==s.end())?0:nxt->se;
		if(s.upper_bound(pii(pos-1,inf))!=s.begin()) s.erase(lst);
//		for(auto x:s) cout<<x.fi<<" "<<x.se<<endl;
//		cout<<"??? "<<pos<<" "<<(s.upper_bound(pii(pos,inf))==s.end())<<endl;
		if(s.upper_bound(pii(pos,inf))!=s.end()) s.erase(s.upper_bound(pii(pos,inf)));
//		for(auto x:s) cout<<x.fi<<" "<<x.se<<endl;
		s.erase(s.upper_bound(pii(pos-1,inf)));
//		for(auto x:s) cout<<x.fi<<" "<<x.se<<endl;
		if(!fg) mx.erase(pii(lmx,lpos));
		if(nxt!=s.end()) mx.erase(pii(rmx,rpos));
//		cout<<"done erase "<<maxn<<" "<<lmx<<" "<<rmx<<" "<<lpos<<" "<<rpos<<endl;
		res+=maxn;
		if(!fg&&!fr)
		{
			s.insert(pii(lpos,lmx+rmx-maxn));
			mx.insert(pii(lmx+rmx-maxn,lpos));
		}
		ans[i]=res;
	}
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
/*
6 1
6 1 7 5 3 2 
-1 1 0 4 4 0 
*/
			
