#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline int read()
{
	int res=0,op=0;
	char ch=getchar();
	while(!isdigit(ch))
	{
		op|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	return op?-res:res;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10^48);
}
inline int gcd(int x,int y)
{
	return y?gcd(y,x%y):x;
}
int n,k;
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read();
	k=read();
	for(re int i=k;i;--i)
	{
		if(gcd(i,n)>1)
		{
			int tmp=gcd(i,n);
			for(re int j=1;j<=tmp;++j)
			{
				for(re int k=1;k<=i/tmp;++k) putchar('1');
				for(re int k=1;k<=n/tmp-i/tmp;++k) putchar('0');
			}
			return 0;
		}
	}
	for(re int i=1;i<=n;++i) putchar('0');
	return 0;
}
