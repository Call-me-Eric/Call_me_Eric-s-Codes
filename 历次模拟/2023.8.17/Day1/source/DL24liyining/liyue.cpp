#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+5;
int a[maxn],pos[maxn],ans[maxn];
struct node{int l,r,id;}q[maxn];

int mua(int x){return x*x;}

int calc(int l,int r)
{
	int cnt=0;
	for(int i=l;i<=r;i++)
		for(int j=l;j<=r&&j!=i;j++)
			if(mua(sqrt(a[i]+a[j]))==(a[i]+a[j])) cnt++;
	return cnt;
}

bool cmp(node a,node b)
{
	if(pos[a.l]==pos[b.l]) return a.r<b.r;
	return a.l<b.l;
}

signed main()
{
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	int n;cin>>n;
	bool flag=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) if(a[i]!=a[i-1]+1) flag=1;
	int len=sqrt(n);
	for(int i=1;i<=n;i++) pos[i]=(i-1)/len+1;
	int qq;cin>>qq;
	for(int i=1;i<=qq;i++) cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+qq+1,cmp);
	if(n<=5000)
	{
		for(int i=1;i<=qq;i++)
			ans[q[i].id]=calc(q[i].l,q[i].r);
		for(int i=1;i<=qq;i++) cout<<ans[i]<<endl;			
	}
	else if(!flag)
	{
		for(int i=1;i<=qq;i++)
		{
			int ll=q[i].l*2+1,rr=q[i].r*2-1;
			ans[q[i].id]=(int)sqrt(rr)-(int)sqrt(ll);
		}
		for(int i=1;i<=qq;i++) cout<<ans[i]<<endl;			
	}
	return 0;
}
