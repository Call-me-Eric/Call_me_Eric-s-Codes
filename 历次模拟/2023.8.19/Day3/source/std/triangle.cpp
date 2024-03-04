#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

int n,k,f[110][110][15],z[110][110],y[1010];

int main()
{
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);

	scanf("%d%d",&n,&k);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=a;b++)
			scanf("%d",&z[a][b]);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=a;b++)
			for (int c=1;c<=k;c++)
				f[a][b][c]=-12345;
	f[1][1][1]=z[1][1];
	for (int a=1;a<n;a++)
		for (int b=1;b<=a;b++)
			for (int c=1;c<=k;c++)
				if (f[a][b][c]!=-12345)
				{
					int v=f[a][b][c]+z[a+1][b];
					for (int d=1;d<=k;d++)
						if (v>=f[a+1][b][d])
						{
							for (int e=k;e>d;e--)
								f[a+1][b][e]=f[a+1][b][e-1];
							f[a+1][b][d]=v;
							break;
						}
					v=f[a][b][c]+z[a+1][b+1];
					for (int d=1;d<=k;d++)
						if (v>=f[a+1][b+1][d])
						{
							for (int e=k;e>d;e--)
								f[a+1][b+1][e]=f[a+1][b+1][e-1];
							f[a+1][b+1][d]=v;
							break;
						}
				}
	int cnt=0;
	for (int a=1;a<=n;a++)
		for (int b=1;b<=k;b++)
			y[++cnt]=f[n][a][b];
	sort(y+1,y+cnt+1);
	printf("%d\n",y[cnt-k+1]);

	return 0;
}
