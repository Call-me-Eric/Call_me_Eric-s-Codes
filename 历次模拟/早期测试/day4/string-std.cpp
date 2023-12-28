#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
using namespace std;
int f[N][N][2],l; //区间dp
//f[i][j][0/1]表示i-1处有一个S，i到j压缩后的长度，0/1表示i到j中有没有S。
/*
初始为j-i+1
f[i][j][0]=min(f[i][j][0],f[i][k][0]+j-k)
f[i][j][1]=min(f[i][j][1],f[i][k][1]+j-k)
f[i][j][1]=min(f[i][j][1],f[i][k][1]+f[k+1][j][1]+1)
判断i,k,j，如果k+1到j可以由i到k重复得到，那么f[i][j][0/1]=min(f[i][j][0/1],f[i][k][0]+1)
*/
char s[N];
 
bool check(int i,int j,int k)
{
    for (int q=0;q<k;q++)
		if (s[i+q]!=s[j+q]) return 0;
    return 1;
}

int main()
{
    scanf("%s",s+1);
    l=strlen(s+1);
    memset(f,0x3f,sizeof(f));
    for (int i=1;i<=l;i++) f[i][i][0]=f[i][i][1]=1;
    for (int d=1;d<=l;d++)
		for (int i=1;i+d<=l;i++)
		{
		    int j=i+d;
		    f[i][j][0]=min(f[i][j][0],d+1);
		    f[i][j][1]=min(f[i][j][1],d+1);
		    for (int k=i;k<j;k++)
		    {
				f[i][j][0]=min(f[i][j][0],f[i][k][0]+j-k);
				f[i][j][1]=min(f[i][j][1],f[i][k][1]+j-k);
				f[i][j][1]=min(f[i][j][1],f[i][k][1]+f[k+1][j][1]+1);
		    }
		    if (d&1)
		    {
				int k=(i+j)>>1,t=(d+1)>>1;
				if (check(i,k+1,t))
				{
				    f[i][j][1]=min(f[i][j][1],f[i][k][0]+1);
				    f[i][j][0]=min(f[i][j][0],f[i][k][0]+1);
				}
		    }
		}
    printf("%d\n",min(f[1][l][0],f[1][l][1]));
    return 0;
}
