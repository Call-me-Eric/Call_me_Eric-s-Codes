#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
int n;
int l,r=2e9+5,mid,ans;
int mi=inf,loc;
vector<int>a[N];
inline int fnd(int i,int x)
{
	int al=0,ar=a[i].size()-1,amid,re=a[i].size();
	while(al<=ar)
	{
		amid=(al+ar)>>1;
		if(a[i][amid]<=x)al=amid+1,re=amid;
		else ar=amid-1;
	}
	return re;
}
inline bool check()
{
	for(int i=0;i<a[1].size();i++)
	{
		int x=a[1][i];
		int mr=x,ml=x;
//		cout<<"__________________\n";
//		cout<<x<<endl;
		for(int j=2;j<=n;j++)
		{
			if(a[j].size()==1)
			{
				ml=min(ml,a[j][0]);
				mr=max(mr,a[j][0]);
				continue;
			}
			int y=fnd(j,x);
//			cout<<j<<' '<<y+1<<endl;
			if(y==a[j].size())
			{
				mr=max(mr,a[j][0]);
//				cout<<j<<' '<<a[j][0]<<endl;
				continue;
			}
			if(y==a[j].size()-1)
			{
//				cout<<j<<' '<<a[j][y]<<endl;
				ml=min(ml,a[j][y]);
				continue;
			}
			if(a[j][y]==x||(a[j][y]>=ml&&a[j][y]<=mr)||(a[j][y+1]>=ml&&a[j][y+1]<=mr))continue;
			
			if(ml-a[j][y]<=a[j][y+1]-mr)ml=min(ml,a[j][y]);//,cout<<j<<' '<<a[j][y]<<endl;
			else mr=max(mr,a[j][y+1]);//,cout<<a[j][y+1]<<endl;
			/*
				可能为：
				10
				-1 11
				-2
				这就得选10 -1 -2 
			*/
			if(mr-ml>mid)break;
		}
		if(mr-ml<=mid)return 1;
	}
	return 0;
}
signed main()
{
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n=read();
	if(n==1)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		int x=read();
		if(x<mi)mi=x,loc=i;
		for(int j=0;j<x;j++)a[i].push_back(read());
		sort(a[i].begin(),a[i].end());
	}
	swap(a[1],a[loc]);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=0;j<a[i].size();j++)cout<<a[i][j]<<' ';
//		cout<<endl;
//	}
//	mid=2;
//	cout<<check();
	while(l<=r)
	{
		mid=(l+r)>>1;
//		cout<<l<<' '<<r<<' '<<mid<<' '<<check()<<endl;
		if(check())r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
/*
4
1 -7
2 10 8
9 -5 -9 2 8 5 4 3 3 8
3 1 6 10

*/
