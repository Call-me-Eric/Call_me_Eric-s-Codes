#include<bits/stdc++.h>
using namespace std;

const int N=105;

int n,k;
int f[N][N];

int main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			scanf("%d",&f[i][j]);
	for(int i=n-1;i>=1;i--)
		for(int j=i;j>=1;j--)
			f[i][j]=max(f[i+1][j],f[i+1][j+1])+f[i][j];
	printf("%d",f[1][1]);
	return 0;
}
