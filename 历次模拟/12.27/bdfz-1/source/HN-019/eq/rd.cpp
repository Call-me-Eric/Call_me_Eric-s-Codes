#include<iostream>
#include<cstdio>
#include<random>
#include<ctime>
#include<cstdlib>
#define mod 998244353
using namespace std;
mt19937 RAND(time(0));
int n=700,q=700;
int main()
{
	freopen("eq.in","w",stdout);
	cout<<n<<' '<<q<<endl;
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=n+1;++j) cout<<RAND()%mod<<' ';
		cout<<endl;
	}
	while (q--)
	{
	    cout<<RAND()%n+1<<' ';
		for (int i=1;i<=n+1;++i) cout<<RAND()%mod<<' ';
		cout<<endl;
	}
	return 0;
}
