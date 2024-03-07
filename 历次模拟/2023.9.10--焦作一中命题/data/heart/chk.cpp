#include "testlib.h"
#include <bits/stdc++.h>
// main 需要接收命令行参数
const int N = 1007;
int A[N][N],B[N][N],vis[N];
int main(int argc, char *argv[])
{
    registerTestlibCmd(argc, argv);
    int T=inf.readInt();
    int tag=0;
    while(T--)
    {
    	int n=inf.readInt(),m=inf.readInt();
    	for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    	A[i][j]=inf.readInt();
    	int k=ans.readInt(),kans=ouf.readInt();
    	if(kans!=k) quitf(_wa,"Wrong Answer");
    	for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    	{
    		B[i][j]=ouf.readInt(0,k);
    		if(A[i][j]==1&&B[i][j]!=0) quitf(_wa,"Wrong Answer");
    		if(A[i][j]==0&&B[i][j]==0) quitf(_wa,"Wrong Answer");
		}
		for(int i=1;i<=n;i++)
		{
			++tag;
			for(int j=1;j<=m;j++)
			if(B[i][j]!=0)
			{
				if(vis[B[i][j]]==tag) quitf(_wa,"Wrong Answer");
				vis[B[i][j]]=tag;
			}
		}
		for(int j=1;j<=m;j++)
		{
			++tag;
			for(int i=1;i<=n;i++)
			if(B[i][j]!=0)
			{
				if(vis[B[i][j]]==tag) quitf(_wa,"Wrong Answer");
				vis[B[i][j]]=tag;
			}
		}
	}
    quitf(_ok, "Perfect");
    return 0;
}
