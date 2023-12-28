#include <bits/stdc++.h>
#define fo(a,b,c) for (a=b; a<=c; a++)
#define fd(a,b,c) for (a=b; a>=c; a--)
#define ll long long
//#define file
using namespace std;

int n,i,j,k,l,t;
ll a[100001],b[100001],c[100001];
ll ans,suma,sumb;
ll p[60];
bitset<100001> d[65],d2;
int D[100001];
int Ans[100001],tot;

bool Insert()
{
	int i,j,k,l;
	
	fo(i,1,n)
	if (d2[i])
	{
		if (!D[i])
		{
			++t;
			d[t]=d2;
			D[i]=t;
			return 1;
		}
		else
		d2^=d[D[i]];
	}
	
	if (d2[0])
	return 0;
	else
	return 1;
}

void work2()
{
	fd(i,n,1)
	if (D[i])
	{
		fo(j,1,t)
		if (j!=D[i] && d[j][i])
		d[j]^=d[D[i]];
	}
	
	fo(i,1,n)
	if (d[D[i]][0])
	Ans[++tot]=i;
}

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	
	p[0]=1;
	fo(i,1,59) p[i]=p[i-1]*2;
	
	scanf("%d",&n);
	fo(i,1,n) scanf("%lld",&a[i]),suma^=a[i];
	fo(i,1,n) scanf("%lld",&b[i]),sumb^=b[i];
	fo(i,1,n) c[i]=a[i]^b[i];
	
	ans=suma+sumb;
	
	fd(i,59,0)
	if (!(suma&p[i]) && !(sumb&p[i]))
	{
		if (i==2)
		n=n;
		
		d2=0;
		fo(j,1,n) if (c[j]&p[i]) d2[j]=1;
		d2[0]=1;
		
		if (Insert())
		ans+=p[i]*2;
	}
	else
	if ( (suma&p[i]) &&  (sumb&p[i]))
	{
		d2=0;
		fo(j,1,n) if (c[j]&p[i]) d2[j]=1;
		d2[0]=0;
		
		if (!Insert())
		ans-=p[i]*2;
	}
	
	work2();
	
	printf("%lld\n",ans);
	return 0;
}
