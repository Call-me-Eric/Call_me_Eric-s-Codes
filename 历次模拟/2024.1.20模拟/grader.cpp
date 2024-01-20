#include "dudu.h"
#include <bits/stdc++.h>
using namespace std;
namespace grader
{
	const char token[] = "Ok.";
	const int N = 1005;
	int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;}
	int n,L,table[N][N],times;
	void init()
	{
		n = read();L = read();
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				table[i][j] = read();
		times = 0;
		found(n,L);
	}
	int query(int qx,int qy)
	{
		if(qx < 1 || qx > n || qy < 1 || qy > n)
		{
			puts("Your query is illegal!");
			exit(0);
		}
		times++;
		if(times > L)
		{
			puts("Too much query!");
			exit(0);
		}
		return table[qx][qy];
	}
	void answer(int ax,int ay)
	{
		if(table[ax][ay] != 1) printf("The number at (%d,%d) is %d\n",ax,ay,table[ax][ay]);
		else printf("%s\n",token);
		printf("You use %d query(s)\n",times);
		exit(0);
	}
}
int query(int qx,int qy){return grader::query(qx,qy);}
void answer(int ax,int ay){grader::answer(ax,ay);}
int main()
{
	freopen("dudu.in","r",stdin);
	freopen("dudu.out","w",stdout);
	grader::init();
	puts("answer() not called!");
	return 0;
}
