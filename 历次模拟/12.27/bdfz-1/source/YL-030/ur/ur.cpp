#include<bits/stdc++.h>
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
int n,k;
int main()
{	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read(),k=read();
	if(n==k)
	{	for(register int i=1;i<=n;++i)printf("1");
		return 0;
	}
	else
		for(register int i=1;i<=n;++i)printf("0");
	return 0;
}

