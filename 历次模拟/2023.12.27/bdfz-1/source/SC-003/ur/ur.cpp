#include<bits/stdc++.h>
using namespace std;
bool chk(int x)
{
	for(int i=2;i*i<=x;++i)
	if(x%i==0)return 0;return 1;
} 
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	if(k==n)for(int i=1;i<=n;++i)putchar('1');
	else if(chk(n))for(int i=1;i<=n;++i)putchar('0');
	return 0;
}
