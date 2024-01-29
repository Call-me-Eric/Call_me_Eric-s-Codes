#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
	long long xr=0,F=1; char cr;
	while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
	while(cr>='0'&&cr<='9') 
		xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
int vis[100000];
int main()
{
	srand(time(0));
	int n=6,w=10; int m=rand()%5+1;
	cout<<n<<" "<<m<<endl;
	for(int i=1;i<=n;i++) 
	{
		int x=rand()%10+1;
		while(vis[x]) x++;
		vis[x]=1;
		cout<<x<<" ";
	} 
	cout<<endl;
	for(int i=1;i<=n;i++) cout<<rand()%10-5<<" ";cout<<endl;
}
