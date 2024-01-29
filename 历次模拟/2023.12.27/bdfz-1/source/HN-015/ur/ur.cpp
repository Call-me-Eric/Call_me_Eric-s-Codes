#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const double pi=acos(-1.0);
const double ppi=pi+pi;
const double eps=1e-6;

int n,k;

namespace Subtask1{
    bool vis[30];
    int Ans[30],Con;
    inline void calc()
    {
	int cnt=0;
	for(rg int i=1;i<=n;i+=1)cnt+=vis[i];
	if(cnt>k)return;
	if(cnt<=Con)return;
	double one=ppi/(double)n;
	double P=0;
	double X=0,Y=0;
	for(rg int i=1;i<=n;i+=1)
	{
	    if(vis[i])
	    {
		X+=sin(P);
		Y+=cos(P);
	    }
	    P+=one;
	}
	if(abs(X)>eps||abs(Y)>eps)return;
	for(rg int i=1;i<=n;i+=1)Ans[i]=vis[i];
	Con=cnt;
    }
    inline void main()
    {
	for(rg int S=0;S<(1<<n);S+=1)
	{
	    for(rg int j=0;j<n;j+=1)
		vis[j+1]=(S>>j)&1;
	    calc();
	}
	for(rg int i=1;i<=n;i+=1)printf("%d",Ans[i]);
    }
}

int main()
{
    file("ur");
    scanf("%d %d",&n,&k);
    if(k&1)k-=1;
    if(k==0)
    {
	for(rg int i=1;i<=n;i+=1)putchar('0');
	return 0;
    }
    if(n<=20)Subtask1::main();
    else
    {
	int Ans=0;
	for(rg int i=1;i<n;i+=1)
	    if(n%i==0)
		Ans=max(Ans,(k/(n/i))*(n/i));
	for(rg int i=1;i<n;i+=1)
	    if(n%i==0&&Ans==(k/(n/i))*(n/i))
	    {
		cerr<<endl;
	    }
    }
    return 0;
}
