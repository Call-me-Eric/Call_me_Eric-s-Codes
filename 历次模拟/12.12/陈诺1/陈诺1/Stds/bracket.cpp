#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int B=400;
char s[160003];
int a[160003];
bool sta[403];
int sum[2][403],pos[2][403];
int f[2][403][803];
int c[803];
inline void build(int x)
{
	int l=x*B,r=(x+1)*B-1,tot=0,pre=0;
	for(int i=l; i<=r; ++i)
	{
		pre+=a[i];
		if(a[i]==1) ++c[B-pre],++tot;
	}
	sum[0][x]=pre,pos[0][x]=tot;
	for(int i=B*2,sum=0,cnt=0; i>=0; --i)
	{
		cnt+=c[i],
		sum+=cnt,
		f[0][x][i]=sum;
	}
	for(int i=l,pre=0; i<=r; ++i)
	{
		pre+=a[i];
		if(a[i]==1) c[B-pre]=0;
	}
	// for(int i=0; i<=B*2; ++i) printf("%d ",f[0][x][i]);
	// puts("");
	tot=pre=0;
	for(int i=l; i<=r; ++i)
	{
		pre-=a[i];
		if(a[i]==-1) ++c[B-pre],++tot;
	}
	sum[1][x]=pre,pos[1][x]=tot;
	for(int i=B*2,sum=0,cnt=0; i>=0; --i)
	{
		cnt+=c[i],
		sum+=cnt,
		f[1][x][i]=sum;
	}
	for(int i=l,pre=0; i<=r; ++i)
	{
		pre-=a[i];
		if(a[i]==-1) c[B-pre]=0;
	}
	// for(int i=0; i<=B*2; ++i) printf("%d ",f[1][x][i]);
	// puts("");
	return ;
}
inline void down(int x)
{
	int l=x*B,r=(x+1)*B-1;
	if(sta[x])
	{
		for(int i=l; i<=r; ++i) a[i]=-a[i];
		sta[x]=0;
	}
	return ;
}
inline ll query(int id,int sdt)
{
	if(sdt>B) return 0;
	else if(sdt>=-B) return f[sta[id]][id][sdt+B];
	else return f[sta[id]][id][0]+1ll*(-B-sdt)*pos[sta[id]][id];
}
signed main()
{
#ifndef local
	freopen("bracket.in","r",stdin),
	freopen("bracket.out","w",stdout);
#endif
	int n=read(),m=read(),L=n/B;
	scanf("%s",s+1);
	for(int i=1; i<=n; ++i)
		if(s[i]=='(') a[i]=1; else a[i]=-1;
	for(int i=0; i<=L; ++i) build(i);
	for(int op,l,r,bl,br; m--;)
	{
		op=read(),l=read(),r=read();
		bl=l/B,br=r/B;
		if(op==1)
		{
			if(bl==br)
			{
				down(bl);
				for(int i=l; i<=r; ++i) a[i]=-a[i];
				build(bl);
			}
			else
			{
				down(bl);
				for(int i=l,tr=(bl+1)*B; i<tr; ++i) a[i]=-a[i];
				build(bl);
				for(int i=bl+1; i<br; ++i) sta[i]^=1;
				down(br);
				for(int i=br*B; i<=r; ++i) a[i]=-a[i];
				build(br);
			}
		}
		else
		{
			int s=0;
			if(bl==br)
			{
				down(bl),build(bl);
				for(int i=l; i<=r; ++i) s+=a[i];
			}
			else
			{
				down(bl),down(br),build(bl),build(br);
				for(int i=l,tr=(bl+1)*B; i<tr; ++i) s+=a[i];
				for(int i=bl+1; i<br; ++i) s+=sum[sta[i]][i];
				for(int i=br*B; i<=r; ++i) s+=a[i];
			}
			int pre=0;
			ll ans=abs(s);
			if(s>0) pre=-s;
			if(bl==br)
			{
				for(int i=l; i<=r; ++i)
				{
					if(a[i]==1)
					{
						++pre;
						if(pre<=0) ans+=1-pre;
					}
					else --pre;
				}
			}
			else
			{
				for(int i=l,tr=(bl+1)*B; i<tr; ++i)
				{
					if(a[i]==1)
					{
						++pre;
						if(pre<=0) ans+=1-pre;
					}
					else --pre;
				}
				for(int i=bl+1; i<br; ++i)
				{
					ans+=query(i,pre),pre+=sum[sta[i]][i];
				}
				for(int i=br*B; i<=r; ++i)
				{
					if(a[i]==1)
					{
						++pre;
						if(pre<=0) ans+=1-pre;
					}
					else --pre;
				}
			}
			if(pre<0)
			{
				pre=-pre;
				ans=ans+1ll*pre*(pre+1)/2;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}