#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[5][5];
int tmp,tmp1,tmp2;
int b1,b2,b3,b4,a1,a2,a3,a4;
double x1,x2,x3;
int T;
void out()
{
	for(int j=1;j<=3;j++)
	{
		for(int i=1;i<=4;i++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
signed main()
{
	
	freopen("sumeru.in","r",stdin);
	freopen("sumeru.out","w",stdout);
	cin>>T;
	while(T--)
	{
		for(int i=1;i<=4;i++)
		{
			for(int j=1;j<=3;j++)
			{
				cin>>a[i][j];
			}
		}
		//step 1
		for(int j=1;j<=3;j++)
		{
			if(a[1][j])
			{
				for(int i=1;i<=4;i++)
				{
					swap(a[i][j],a[i][1]);
				}
			}
		}
		b1=a[1][1],b2=a[2][1],b3=a[3][1],b4=a[4][1];
		
		if(b1!=0)
		{
			for(int j=2;j<=3;j++)
			{
				tmp=__gcd(a[1][1],a[1][j]);
				tmp1=a[1][j]/tmp;
				tmp2=a[1][1]/tmp;
				for(int i=1;i<=4;i++)
				{
					a[i][j]=a[i][j]*tmp2-a[i][1]*tmp1;
				}
			}
		}
		//step 2
		for(int j=2;j<=3;j++)
		{
			if(a[2][j])
			{
				for(int i=1;i<=4;i++)
				{
					swap(a[i][j],a[i][2]);
				}
			}
		}
		a2=a[2][2],a3=a[3][2],a4=a[4][2];
		if(a2!=0)
		{
			for(int j=3;j<=3;j++)
			{
				tmp=__gcd(a[2][2],a[2][j]);
				tmp1=a[2][j]/tmp;
				tmp2=a[2][2]/tmp;
				for(int i=1;i<=4;i++)
				{
					a[i][j]=a[i][j]*tmp2-a[i][2]*tmp1;
				}
			}
		}
//		cout<<a[3][3]<<" "<<a[4][3]<<endl;
		if(a[3][3]==0)
		{
			if(a[4][3]!=0)
			{
				cout<<"NO"<<endl;
				continue;
			}
			else
			{
				cout<<"YES"<<endl;
				continue;
			}
		}
		x3=1.0*a[4][3]/a[3][3];
		if(a2==0)
		{
			cout<<"YES"<<endl;
			continue;
		}
		x2=1.0*(a4-a3*x3)/a2;
		if(b1==0)
		{
			cout<<"NO"<<endl;
			continue;
		}
		x1=1.0*(b4-b3*x3-b2*x2)/b1;
//		cout<<x1<<" "<<x2<<" "<<x3<<endl;
		if(x1>=0&&x2>=0&&x3>=0)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
}
/*
0 0 1 0 1 0 1 0 0 1 2 3
0 0 0 0 0 0 0 0 0 1 2 3
*/
