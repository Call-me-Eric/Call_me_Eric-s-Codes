#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1000005;
const ll mod=998244353;
const int inf=0x3f3f3f3f;
inline int rd()
{
    int x=0; bool f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar())
        if(ch=='-') f=0;
    for(;isdigit(ch);ch=getchar())
        x=x*10+(ch^48);
    return f?x:-x;
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n=rd(),k=rd();
	int ans=n;
	for(int i=2;i<=n;i++)
	{
		if(n%i==0)
			if(k/i*i>k/ans*ans)
				ans=i;
	}
	int t=k/ans;
	int bl=n/ans;
	for(int i=1;i<=ans;i++)
	{
		for(int j=1;j<=t;j++)
			putchar('1');
		for(int j=t+1;j<=bl;j++)
			putchar('0');
	}
    return 0;
}
