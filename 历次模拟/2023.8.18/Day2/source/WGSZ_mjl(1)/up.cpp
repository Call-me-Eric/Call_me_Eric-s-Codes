#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
int n,m;
struct no
{
	int x,y,chu;bool f;
}a[N<<5];
map<int,int>mp;
int tot;
signed main()
{
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read();
		while(x&&y)
		{
//			cout<<x<<' '<<y<<' ';
			if(x>y)
			{
				a[++tot]=(no){x%y,x/y,y,1};
				if(x%y==0)mp[y]++;
				x%=y;
			}
			else
			{
				a[++tot]=(no){y%x,y/x,x,0};
				if(y%x==0)mp[x]++;
				y%=x;
			}
//			cout<<a[tot].x<<' '<<a[tot].y<<' '<<a[tot].f<<endl;
		}
	}
//	cout<<tot<<endl;
	while(m--)
	{
//		cout<<"____________________\n";
//		auto xx=clock();
		int ans=0;
		int x=read(),y=read();
		if(x==y)
		{
			printf("%lld\n",mp[x]);
//			cout<<(clock()-xx)*1.0/CLOCKS_PER_SEC<<endl;
			continue;
		}
		for(int i=1;i<=tot;i++)
		{
			if(x>y)
			{
				if(a[i].f&&a[i].chu==y&&x/y<=a[i].y&&x%y==a[i].x)ans++;//,cout<<a[i].x<<' '<<a[i].y<<' '<<a[i].f<<endl;
			}
			else if(!a[i].f&&a[i].chu==x&&y/x<=a[i].y&&y%x==a[i].x)ans++;//,cout<<a[i].x<<' '<<a[i].y<<' '<<a[i].f<<endl;
		}
		printf("%lld\n",ans);
//		cout<<(clock()-xx)*1.0/CLOCKS_PER_SEC<<endl;
	}
	return 0;
}
/*
2 2
7 14
7 14
7 7
7 14

*/
