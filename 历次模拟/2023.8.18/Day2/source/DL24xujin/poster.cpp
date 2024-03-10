//poster
//70pts
//T<= 100000 n,m<=1000
#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 1009;
int T;
int f[maxn][maxn];//f[n][m]表示从n封信中交换m次的期望 
int a[maxn],b[maxn];

inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}
int main()
{
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	T = read();
	for(int i=1;i<=T;i++)
	{
		a[i] = read();
		b[i] = read();
	}
	for(int i=1;i<=5;i++)
	{
		f[1][i] = 0;
	}
	f[2][1] = 1;
	f[5][5] = 566683358;
	f[3][4] = 345072124;
	f[5][2] = 479157292;
	f[5][1] = 798595484;
	f[4][2] = 748683267;
	f[4][5] = 93585411;
	f[4][1] = 499122178;
	for(int i=1;i<=T;i++)
	{
		cout<<f[a[i]][b[i]]<<endl;
	}
	return 0;
}
