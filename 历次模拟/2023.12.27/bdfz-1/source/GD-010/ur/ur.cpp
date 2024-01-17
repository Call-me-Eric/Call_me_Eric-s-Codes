#include<bits/stdc++.h>
using namespace std;
int n,k;
int tn=1,pn=1;
int np;
bool ans[1000006];
vector<int> p;
int main()
{
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(n==k)
	{
		for(int i=1;i<=n;i++)	putchar('1');
		putchar('\n');
		return 0;
	}
	if(k<=1)
	{
		for(int i=1;i<=n;i++)	putchar('0');
		putchar('\n');
		return 0;
	}
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			p.push_back(i);
			tn*=i;
			n/=i;
			while(n%i==0)	n/=i,pn*=i;
		}
	}
	tn*=n;
	if(n!=1)	p.push_back(n);
	np=p.size();
	n=tn*pn;
	if(np==1)
	{
		int nk=k/tn;
		for(int i=1;i<=tn;i++)
		{
			for(int j=1;j<=nk;j++)		putchar('1');
			for(int j=nk+1;j<=pn;j++)	putchar('0');
		}
		return 0;
	}
	if(np==2)
	{
		int a=0,b=0,c=0;
		for(int i=0;i<p[1];i++)
			for(int j=0;j<p[0];j++)
			{
				int sm=i*p[0]+j*p[1];
				if(sm>k)	break;
				if((i>0)+(j>0)>pn)	break;
				int tk=(k-sm)/tn;
				tk=min(tk,pn-(i>0)-(j>0));
				sm+=tk*tn;
				if(sm>a*p[0]+b*p[1]+c*tn)
				{
					a=i;
					b=j;
					c=tk;
				}
			}
		pn=n/p[0]/p[1];
		for(int i=1;i<=c;i++)
			for(int j=0;j<p[0]*p[1];j++)
				ans[j*pn+i]=1;
		for(int i=0;i<a;i++)
			for(int j=0;j<p[0];j++)
				ans[j*pn*p[1]+i*pn+c+1]=1;
		for(int i=0;i<b;i++)
			for(int j=0;j<p[1];j++)
				ans[j*pn*p[0]+i*pn+c+2]=1;
		int cnt;
		for(int i=1;i<=tn*pn;i++)	cout<<ans[i];//,cnt+=ans[i];
		cout<<'\n';
		return 0;
	}
	while(k--)
	for(int i=0;i<np;i++)
	{
		for(int j=i+1;j<np;j++)
		{
			swap(p[0],p[i]);
			swap(p[1],p[j]);
			tn=p[0]*p[1];
			pn=n/tn;
			int a=0,b=0,c=0;
			for(int i=0;i<p[1];i++)
				for(int j=0;j<p[0];j++)
				{
					int sm=i*p[0]+j*p[1];
					if(sm>k)	break;
					if((i>0)+(j>0)>pn)	break;
					int tk=(k-sm)/tn;
					tk=min(tk,pn-(i>0)-(j>0));
					sm+=tk*tn;
					if(sm>a*p[0]+b*p[1]+c*tn)
					{
						a=i;
						b=j;
						c=tk;
					}
				}
			if(a*p[0]+b*p[1]+c*tn==k)
			{
				pn=n/p[0]/p[1];
				for(int i=1;i<=c;i++)
					for(int j=0;j<p[0]*p[1];j++)
						ans[j*pn+i]=1;
				for(int i=0;i<a;i++)
					for(int j=0;j<p[0];j++)
						ans[j*pn*p[1]+i*pn+c+1]=1;
				for(int i=0;i<b;i++)
					for(int j=0;j<p[1];j++)
						ans[j*pn*p[0]+i*pn+c+2]=1;
				int cnt;
				for(int i=1;i<=tn*pn;i++)	cout<<ans[i];//,cnt+=ans[i];
				cout<<'\n';
				return 0;
			}
			swap(p[1],p[j]);
			swap(p[0],p[i]);
		}
	}
	return 0;
}
