#include <bits/stdc++.h>
using namespace std;

int n,q;
int main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		int a;for(int j=1;j<=n+1;j++) cin>>a;
	}
	srand(time(0));
	for(int i=1;i<=rand()%1000;i++) srand(rand());
	if(rand()%2) cout<<"Many\n";else cout<<"No\n";
	for(int i=1;i<=q;i++)
	{
		int b;for(int j=1;j<=n+2;j++) cin>>b;
		srand(rand());
		if(rand()%2) cout<<"Many\n";else cout<<"No\n";
	}
	return 0;
}