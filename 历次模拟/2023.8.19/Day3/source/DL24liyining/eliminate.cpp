#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int c[100005],tt;
struct node{int t,p;}q[maxn];
bool vis[maxn];

inline int read()
{
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(x == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
	return x * f;
}

bool cmp(node a,node b)
{return a.t<b.t;}

int check(int x)
{
	int cnt=0;
	for(int i=1;i<=tt;i++)
		if(q[i].t==x&&!vis[q[i].p]) cnt++,vis[q[i].p]=1;
	return cnt;
}

int main()
{
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	int n,m;cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		for(int j=1;j<=c[i];j++) tt++,cin>>q[tt].t,q[tt].p=i;
	}
	sort(q+1,q+1+n,cmp);
	int minn=114514;
	for(int i=tt;i;i--)
	{
		int cnt=1;
		for(int j=1;j<=tt;j++) vis[j]=0;
		vis[q[i].p]=1;
		for(int j=i-1;j;j--)
		{
			cnt+=check(q[j].t);
			if(cnt==n) minn=min(minn,q[i].t-q[j].t);
		}
	}
	if(n==1) cout<<0;
	else 
	{
		cout<<minn;
//		for(int i=1;i<=tt;i++) cout<<q[i].t<<" "<<q[i].p<<endl;
	}
	return 0;
}
