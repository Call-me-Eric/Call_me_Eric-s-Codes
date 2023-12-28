#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
using namespace std;
int f[N][N][2],l; //����dp
//f[i][j][0/1]��ʾi-1����һ��S��i��jѹ����ĳ��ȣ�0/1��ʾi��j����û��S��
/*
��ʼΪj-i+1
f[i][j][0]=min(f[i][j][0],f[i][k][0]+j-k)
f[i][j][1]=min(f[i][j][1],f[i][k][1]+j-k)
f[i][j][1]=min(f[i][j][1],f[i][k][1]+f[k+1][j][1]+1)
�ж�i,k,j�����k+1��j������i��k�ظ��õ�����ôf[i][j][0/1]=min(f[i][j][0/1],f[i][k][0]+1)
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
