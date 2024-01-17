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
int main()
{
	for(int i=1;i<=10000;i++)
	{
		cerr<<i<<endl;
		system("data.exe > qwq.in");
		system("distanced.exe < qwq.in > std.out");
		system("baoli.exe < qwq.in > baoli.out");
		if(system("fc std.out baoli.out")) break;
	}
	return 0;
}
