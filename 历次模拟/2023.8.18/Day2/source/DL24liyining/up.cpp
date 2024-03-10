#include <bits/stdc++.h>
using namespace std;
#define int long long
#define A p[i].a
#define B p[i].b

const int maxn=50005;
struct node{int a,b;}p[maxn];

int gcd(int x,int y) 
{return !y?x:gcd(y,x%y);}

signed main()
{
//	freopen("up.in","r",stdin);
//	freopen("up.out","w",stdout);
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>p[i].a>>p[i].b;
	while(q--)
	{
		int c,d;cin>>c>>d;
		bool f1=0,f2=0;
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(c>p[i].a||d>p[i].b) continue;
			if(c==p[i].a&&d==p[i].b) cnt++;
//			for(int k=1;k<=c/p[i].a;k++)
//			{
//				if(c==(k+1)*p[i].a+k*p[i].b){f1=1;break;}
//				if(c<(k+1)*p[i].a+k*p[i].b) break;
//			}
//			for(int k=1;k<=d/p[i].b;k++)
//			{
//				if(d==(k+1)*p[i].a+k*(p)) cnt++;
//			}
			if(A!=c)
			{
				for(int j=1;j<=100;j++)
					for(int k=1;k<=100;k++) if(j*c+k*d==A&&gcd(j,k)==1) f1=1;
			}
			else f1=1;
			if(B!=d)
			{
				for(int j=1;j<=100;j++)
					for(int k=1;k<=100;k++) if(j*c+k*d==B&&gcd(j,k)==1) f2=1;		
			}
			else f2=1;
			if(f1&&f2) cnt++;
		}
		cout<<cnt<<endl;
	}
	return 0;
}
