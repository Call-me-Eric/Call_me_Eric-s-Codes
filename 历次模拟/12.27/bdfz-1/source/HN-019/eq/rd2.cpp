#include<iostream>
#include<cstdio>
#include<random>
#include<ctime>
#include<cstdlib>
#define mod 998244353
using namespace std;
mt19937 RAND(time(0));
int n,q;
int main()
{
	freopen("eq.in","w",stdout);
	n=RAND()%10+1,q=RAND()%100+1;
	cout<<n<<' '<<q<<endl;
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=n+1;++j)
		{
			if (RAND()%4==0) cout<<RAND()%mod<<' ';
			else cout<<RAND()%2<<' ';
		}
		cout<<endl;
	}
	while (q--)
	{
	    cout<<RAND()%n+1<<' ';
		for (int i=1;i<=n+1;++i)
		{
			if (RAND()%4==0) cout<<RAND()%mod<<' ';
			else cout<<RAND()%2<<' ';
		}
		cout<<endl;
	}
	return 0;
}
