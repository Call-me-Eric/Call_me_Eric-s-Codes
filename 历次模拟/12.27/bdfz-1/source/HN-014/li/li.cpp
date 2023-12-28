#include<bits/stdc++.h>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
int n,m;
signed main(){
	file("li");
	n=read();m=read();
	for(int i=1,u,v;i<=m;i++)u=read(),v=read();
	if(n<=1)return printf("0 %d\n",1),0;
	if(n<=2)return printf("0 %d\n",2+m),0;
	if(n<=3)return printf("%d %d\n",m==3,m==3?3:(m==2?6:4)),0;
	return 0;
}
