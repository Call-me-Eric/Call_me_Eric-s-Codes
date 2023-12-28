#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
char s[2003][2003];
signed main()
{
#ifndef local
	freopen("chess.in","r",stdin),
	freopen("chess.out","w",stdout);
#endif
	int n=read(),m=read();
	for(int i=1; i<=n; ++i)
	scanf("%s",s[i]+1);
	int as=1;
	for(int i=1; i<=n; ++i)
	for(int j=1; j<=m; ++j)
	{
		int st=1;
		for(int t=-1; t<=1; t++)
			for(int k=-1; k<=1; k++)
			{
				if(abs(t)+abs(k)!=1) continue;
				int x=i+t,y=j+k;
				if(1<=x&&x<=n
				&&1<=y&&y<=m
				&&s[x][y]!=s[i][j]) st=0;
			}
		if(st) as=(as<<1)%p;
	}
	printf("%lld\n",as);
	return 0;
}