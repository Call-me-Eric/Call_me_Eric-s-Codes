#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<vector>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int N=2e5+5;
struct tree
{
	int l,r,minn,maxx;
}t[N*4];
int n,L[N],R[N],a[N],limit[N],m;
void pushup(int k)
{
	t[k].minn=min(t[k*2].minn,t[k*2+1].minn);
	t[k].maxx=max(t[k*2].maxx,t[k*2+1].maxx);
}
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;
	if(l==r)
	{
		t[k].minn=L[l];
		t[k].maxx=R[l];
		return;
	}
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
}
void change(int k,int x,int v)
{
	if(t[k].l==t[k].r)
	{
		if(v) t[k].minn=n+1,t[k].maxx=0;
		else t[k].minn=L[x],t[k].maxx=R[x];
		return;
	}
	if(x<=t[k*2].r) change(k*2,x,v);
	else change(k*2+1,x,v);
	pushup(k);
}
multiset<int> s;
map<int,int> mp;
int tot;
int getid(int x)
{
	if(!mp[x]) mp[x]=++tot;
	return mp[x];
}
vector<int> v[N],v2[N];
bool check(int l,int r)
{
//	cout<<"chk"<<l<<' '<<r<<" "<<t[1].minn<<" "<<t[1].maxx<<endl; 
	return l<=t[1].minn&&t[1].maxx<=r;
}
void solve()
{
	tot=0;
	mp.clear();
	s.clear();
	n=read();m=read();
	for(int i=1;i<=n;i++)
	v[i].clear(),v2[i].clear();
	for(int i=1;i<=n;i++)
	a[i]=read(),a[i]=getid(a[i]),v2[a[i]].push_back(i);
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		v[x].push_back(x);
		v[y+1].push_back(-x);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<v[i].size();j++)
		if(v[i][j]>0) s.insert(v[i][j]);
		else s.erase(s.find(-v[i][j]));
		if(s.empty()) limit[i]=0,L[i]=n+1,R[i]=0;
		else limit[i]=(*s.begin());
	}
	for(int i=1;i<=n;i++)
	{
		if(limit[i]==0)
		{
//			 cout<<i<<' '<<L[i]<<" "<<R[i]<<endl;
			continue;
		}
		if(limit[i]==i)
		{
			L[i]=n+1;
			R[i]=0;		
		}
		else
		{
			int l=0,r=v2[a[i]].size()-1;
			L[i]=n+1,R[i]=0;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(v2[a[i]][mid]>=limit[i]) L[i]=v2[a[i]][mid],r=mid-1;
				else l=mid+1;
			}
			if(L[i]>=i) L[i]=n+1;
			l=0,r=v2[a[i]].size()-1;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(v2[a[i]][mid]<i) R[i]=v2[a[i]][mid],l=mid+1;
				else r=mid-1;
			}
			if(R[i]<limit[i]) R[i]=0;
		}
	}
    for(int i = 1;i <= n;i++)
		 cout<<i<<' '<<L[i]<<" "<<R[i]<<endl;
	build(1,1,n);
	int ans=n, ll = 0, rr = 0;
	for(int l=1,r=0;l<=n;l++)
	{
		while(r<n&&!check(l,r)) r++,change(1,r,1);
		if(check(l,r)){
            if(ans >= max(0,r - l + 1)){
                ans = max(0,r-l+1);
                ll = l;rr = r;
            }
        }
//		 cout<<l<<' '<<r<<endl;
		change(1,l,0);
	}
    // if(ans == 57905)cout << "ll = " << ll << " rr = " << rr << endl;
	cout<<ans<<endl;
    for(int i = 3133;i <= 3140;i++)printf("a[%d]=%d\n",i,a[i]);
}
int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout); 
	int T=read();
	while(T--) solve();
 	return 0;
}

/*
1 5 2
0 5 4 9 4 
1 5
3 4
lgsblgsb
*/
