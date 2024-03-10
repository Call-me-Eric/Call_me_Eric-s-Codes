#include<bits/stdc++.h>
using namespace std;
double a[5][5];
double tmp,tmp1;
double x1,x2,x3,x[5];
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
		if(a[1][1]!=0)
		{
			for(int j=2;j<=3;j++)
			{
				tmp1=a[1][j]/a[1][1];
				for(int i=1;i<=4;i++)
				{
					a[i][j]=a[i][j]-a[i][1]*tmp1;
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
		if(a[2][2]!=0)
		{
			for(int j=3;j<=3;j++)
			{
				tmp1=a[2][j]/a[2][2];
				for(int i=1;i<=4;i++)
				{
					a[i][j]=a[i][j]-a[i][2]*tmp1;
				}
			}
		}
//		out();
		for(int j=3;j>=1;j--)
		{
			for(int i=3;i>=j+1;i--)
			{
				a[4][j]-=a[i][j]*x[i];
			}
			if(a[j][j]==0)
			{
				if(a[4][j]==0)
				{
					x[j]=0;
					continue;
				}
				else
				{
					cout<<"NO"<<endl;
					goto ed;
				}
			}
			else
				x[j]=1.0*a[4][j]/a[j][j];
		}
		for(int i=1;i<=3;i++)
		{
			if(x[i]<0)
			{
				cout<<"NO"<<endl;
				goto ed;
			}
		}
		cout<<"YES"<<endl;
		ed:
			continue;
	}
}
/*
2
4 2 4 4 3 0 2 1 2 9 10 6
0 3 1 0 1 3 4 0 4 4 1 10

*/
