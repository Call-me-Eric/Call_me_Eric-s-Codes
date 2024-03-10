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
int T;
int a[5][5];
int a1,b1,c1,a2,b2,c2;
struct no
{
	int x,y;bool f;
	no(){x=y=f=0;}
	bool operator == (const no &aa)const{return x==aa.x&&y==aa.y&&f==aa.f;}
};
int x,y,g;
void yu(no &xx)
{
	if(!xx.x||!xx.y)
	{
		xx.y=1;
		return ;
	}
	xx.f=(xx.x<0)^(xx.y<0);
	xx.x=abs(xx.x);xx.y=abs(xx.y);
	g=__gcd(xx.x,xx.y);
	xx.x/=g;xx.y/=g;
}
no jia(no aa,no bb)
{
	no cc;
	cc.x=aa.x*bb.y+bb.x*aa.y;
	cc.y=aa.y*bb.y;
	yu(cc);
	return cc;
}
no chen(no aa,int xx)
{
	no bb=aa;
	bb.x*=xx;
	yu(bb);
	return bb;
}
no jian(int xx,no aa)
{
	no bb;
	if(xx*aa.y<aa.x)
	{
		bb.f=1;
		return bb;
	}
	bb.x=aa.y*xx-aa.x;
	bb.y=aa.y;
	yu(bb);
	return bb;
}
no chu(no aa,int xx)
{
	no bb;
	if(!xx)
	{
		bb.x=0;
		return bb;
	}
	bb.x=aa.x;
	bb.y=aa.y*xx;
	yu(bb);
	return bb;
}
void pr(no aa)
{
	cout<<aa.x<<' '<<aa.y<<' '<<aa.f<<endl;
}
signed main()
{
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	T=read();
	while(T--)
	{
		no x1,x2,x3;
		for(int i=1;i<=4;i++)for(int j=1;j<=3;j++)a[i][j]=read();
		a1=a[2][1]*a[1][2]-a[2][2]*a[1][1];
		b1=a[3][1]*a[1][2]-a[3][2]*a[1][1];
		c1=a[4][1]*a[1][2]-a[4][2]*a[1][1];
		a2=a[2][2]*a[1][3]-a[2][3]*a[1][2];
		b2=a[3][2]*a[1][3]-a[3][3]*a[1][2];
		c2=a[4][2]*a[1][3]-a[4][3]*a[1][2];
		x=b2*c1-b1*c2,y=a1*b2-a2*b1;
		x2.x=x;x2.y=y;
		yu(x2);
		swap(a1,b1);swap(a2,b2);swap(c1,c2);
		x=b2*c1-b1*c2,y=a1*b2-a2*b1;
		x3.x=x;x3.y=y;
		yu(x3);
//		pr(x2);pr(x3);
		if(x2.f||x3.f)
		{
			puts("NO");
			continue;
		}
		no d1,d2,d3;
		d1=jia(chen(x2,a[2][1]),chen(x3,a[3][1]));
		d2=jia(chen(x2,a[2][2]),chen(x3,a[3][2]));
		d3=jia(chen(x2,a[2][3]),chen(x3,a[3][3]));
//		pr(d1);pr(d2);pr(d3);
//		cout<<endl;
		d1=jian(a[4][1],d1);
		d2=jian(a[4][2],d2);
		d3=jian(a[4][3],d3);
//		pr(d1);pr(d2);pr(d3);
		if(d1.f||d2.f||d3.f)
		{
			puts("NO");
			continue;
		}
		if((d1.x==0&&a[1][1])||(d2.x==0&&a[1][2])||(d3.x==0&&a[1][3]))
		{
			puts("NO");
			continue;
		}
		if(!d1.x&&!d2.x&&!d3.x)
		{
			puts("YES");
			continue;
		}
		d1=chu(d1,a[1][1]);
		d2=chu(d2,a[1][2]);
		d3=chu(d3,a[1][3]);
		if((d1==d2&&d1.x&&d2.x)&&(d2==d3&&d2.x&&d3.x)&&(d1==d3&&d1.x&&d3.x))puts("YES");
		else puts("NO");
	}
	return 0;
}
/*
1
0 2 2 0 4 1 0 2 4 0 2 1

*/
