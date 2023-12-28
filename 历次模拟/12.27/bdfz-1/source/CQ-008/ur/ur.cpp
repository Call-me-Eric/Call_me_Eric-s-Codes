#include <iostream>
using namespace std;
int n,k;
int gcd(int a,int b)
{
	if(a<b) swap(a,b);
	if(a%b==0) return b;
	return gcd(b,a%b);
}
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin>>n>>k;
	for (int i=k;i;i--)
	{
		int x=gcd(n,i);
		if(x==1) continue;
		int y=i/x,z=n/x;
		for (int j=1;j<=x;j++)
		{
			for (int t=1;t<=y;t++) cout<<"1";
			for (int t=1;t<=z-y;t++) cout<<"0";
		}
		cout<<endl;
		//cout<<i<<endl;
		return 0;
	}
	for (int i=1;i<=n;i++) cout<<"0";
	cout<<endl;
	return 0;
}
