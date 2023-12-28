#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int n=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		n=n*10+ch-'0';
		ch=getchar();
	}
	return n*f;
}
int yu[500005],yv[500005],yw[500005];
int bu[500005],bv[500005],bw[500005],pos[500005];
bool xz[500005];
int nf[305],pf[305],fa[305];
int findnf(int n)
{
	if(nf[n]==n)return n;
	return nf[n]=findnf(nf[n]);
}
int findpf(int n)
{
	if(pf[n]==n)return n;
	return pf[n]=findpf(pf[n]);
}
int findf(int n)
{
	if(fa[n]==n)return n;
	return fa[n]=findf(fa[n]);
}
int n,m;
bool check(int bh,int r,int g,int b)
{
	int tx=0,ty=0;
	for(int i=1;i<=n;i++)pf[i]=nf[i];
	if(bh!=0)
	{
		if(bw[bh]=='r')r--;
		if(bw[bh]=='g')g--;
		if(bw[bh]=='b')b--;
		if(findpf(bu[bh])==findpf(bv[bh]))return false;
		pf[findpf(bu[bh])]=findpf(bv[bh]);
	}
	if(r<0||g<0||b<0)return false;
	int xj=0,sj=0;
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]!='r'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
		}
	}
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='r'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			xj++;
		}
	}
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='r'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			sj++;
		}
	}
	if(r<xj||r>sj)return false;
	xj=0;
	sj=0;
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]!='g'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
		}
	}
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='g'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			xj++;
		}
	}
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='g'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			sj++;
		}
	}
	if(g<xj||g>sj)return false;
	xj=0;
	sj=0;
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]!='b'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
		}
	}
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='b'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			xj++;
		}
	}
	for(int i=1;i<=n;i++)fa[i]=pf[i];
	for(int i=bh+1;i<=m;i++)
	{
		if(bw[i]=='b'&&findf(bu[i])!=findf(bv[i]))
		{
			fa[findf(bu[i])]=findf(bv[i]);
			sj++;
		}
	}
	if(b<xj||b>sj)return false;
	return true;
}
int main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	int r,g,b;
	int pr,pg,pb;
	r=read();
	g=read();
	b=read();
	pr=r;
	pg=g;
	pb=b;
	m=read();
	n=r+g+b+1;
	for(int i=1;i<=m;i++)
	{
		yu[i]=read();
		yv[i]=read();
		yw[i]=getchar();
		pos[i]=i;
		while(yw[i]<'a'||yw[i]>'z')yw[i]=getchar();
	}
	for(int i=1;i<=m;i++)swap(pos[i],pos[rand()%i+1]);
	for(int i=1;i<=m;i++)
	{
		bu[pos[i]]=yu[i];
		bv[pos[i]]=yv[i];
		bw[pos[i]]=yw[i];
	}
	for(int i=1;i<=n;i++)nf[i]=i;
	if(check(0,r,g,b)==false)
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for(int i=1;i<=m;i++)
	{
		if(check(i,r,g,b))
		{
			xz[i]=true;
			nf[findnf(bu[i])]=findnf(bv[i]); 
			if(bw[i]=='r')r--;
			if(bw[i]=='g')g--;
			if(bw[i]=='b')b--;
		}
		else
		{
			xz[i]=false;
		}
	}
	for(int i=1;i<=m;i++)printf("%d",xz[pos[i]]);
	printf("\n");
	return 0;
	/*for(int i=1;i<=n;i++)nf[i]=i;
	int sr=0,sg=0,sb=0;
	for(int i=1;i<=m;i++)
	{
		if(xz[pos[i]])
		{
			nf[findnf(yu[i])]=findnf(yv[i]);
			if(yw[i]=='r')sr++;
			if(yw[i]=='g')sg++;
			if(yw[i]=='b')sb++;
		}
	}
	printf("%d %d %d\n",sr,sg,sb);
	if(sr!=pr||sg!=pg||sb!=pb)
	{
		printf("wa number not correct\n");
		return 0;
	}
	for(int i=1;i<=n;i++)if(findnf(i)!=findnf(1))
	{
		printf("wa not connected\n");
		return 0;
	}
	printf("ac\n");
	return 0;*/
}
