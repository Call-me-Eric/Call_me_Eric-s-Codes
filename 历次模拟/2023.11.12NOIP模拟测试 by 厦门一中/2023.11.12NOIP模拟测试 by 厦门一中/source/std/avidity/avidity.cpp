#include<bits/stdc++.h>
#define ll long long
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*o=obuf;
#define g()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int s=0;char c=g();
    for(;!isdigit(c);c=g());
    for(;isdigit(c);c=g())
        s=s*10+c-'0';
    return s;
}
inline void write(ll x)
{
    static char buf[20];
    static int len=-1;
    do buf[++len]=x%10,x/=10;while(x);
    while(len>=0)putchar(buf[len--]+'0');
    putchar('\n');
}
int n,m,a[50005],len,block,maxn;
int L[250],R[250],pos[50005];
int t[50005],tt[50005];
int cnt[350][50005],pre[50005],nxt[50005];
int tot1[50005],tot2[50005],tot3[50005];
int v1[2][100][50005],v2[2][100][50005],v3[2][100][50005];
ll ans[250][250],lst;
bool vis[50005],v[50005];
inline void add(int a,int b,int c)
{
	v[a]=v[b]=v[c]=1;
	v1[0][++tot1[a]][a]=b,v1[1][tot1[a]][a]=c;
	v2[0][++tot2[b]][b]=a,v2[1][tot2[b]][b]=c;
	v3[0][++tot3[c]][c]=a,v3[1][tot3[c]][c]=b;
}
void init()
{
    for(int i=1;i*i<=maxn;i+=2)
        for(int j=i+2;(i*i+j*j)/2<=maxn;j+=2)
		{
            if(__gcd(i,j)!=1)continue;
            int a=i*j,b=(j*j-i*i)/2,c=(i*i+j*j)/2;
			for(int k=1;c*k<=maxn;++k)
				if(vis[a*k]&vis[b*k]&vis[c*k])
					add(a*k,b*k,c*k);
		}
}
ll cal(int l,int r)
{
	ll res=0;
	for(int i=L[r];i<=R[r];++i)
	{
		for(int j=1;j<=tot1[a[i]];++j)
		{
			int x=v1[0][j][a[i]],y=v1[1][j][a[i]];
			res+=(cnt[l][x]-cnt[l-1][x])*(cnt[l][y]-cnt[l-1][y])+(cnt[l][x]-cnt[l-1][x])*(cnt[r-1][y]-cnt[l][y])+(cnt[l][y]-cnt[l-1][y])*(cnt[r-1][x]-cnt[l][x]);
		}
		for(int j=1;j<=tot2[a[i]];++j)
		{
			int x=v2[0][j][a[i]],y=v2[1][j][a[i]];
			res+=(cnt[l][x]-cnt[l-1][x])*(cnt[l][y]-cnt[l-1][y])+(cnt[l][x]-cnt[l-1][x])*(cnt[r-1][y]-cnt[l][y])+(cnt[l][y]-cnt[l-1][y])*(cnt[r-1][x]-cnt[l][x]);
		}
		for(int j=1;j<=tot3[a[i]];++j)
		{
			int x=v3[0][j][a[i]],y=v3[1][j][a[i]];
			res+=(cnt[l][x]-cnt[l-1][x])*(cnt[l][y]-cnt[l-1][y])+(cnt[l][x]-cnt[l-1][x])*(cnt[r-1][y]-cnt[l][y])+(cnt[l][y]-cnt[l-1][y])*(cnt[r-1][x]-cnt[l][x]);
		}
	}
	for(int i=L[l];i<=R[l];++i)
	{
		for(int j=1;j<=tot1[a[i]];++j)
		{
			int x=v1[0][j][a[i]],y=v1[1][j][a[i]];
			res+=(cnt[r][x]-cnt[r-1][x])*(cnt[r][y]-cnt[r-1][y]);
		}
		for(int j=1;j<=tot2[a[i]];++j)
		{
			int x=v2[0][j][a[i]],y=v2[1][j][a[i]];
			res+=(cnt[r][x]-cnt[r-1][x])*(cnt[r][y]-cnt[r-1][y]);
		}
		for(int j=1;j<=tot3[a[i]];++j)
		{
			int x=v3[0][j][a[i]],y=v3[1][j][a[i]];
			res+=(cnt[r][x]-cnt[r-1][x])*(cnt[r][y]-cnt[r-1][y]);
		}
	}
	return res;
}
int ps[50005],tempn,l_[50005],r_[50005];
void input()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),maxn=max(maxn,a[i]),vis[a[i]]=true;
	init();
	
	int tt=0;
	for(int i=1;i<=n;i++)
		if(vis[a[i]])ps[++tt]=i;
	int p=1;
	for(int i=1;i<=n;i++)
	{
		l_[i]=p;
		if(ps[p]==i)++p;
	}
	p=tt;
	for(int i=n;i;i--)
	{
		r_[i]=p;
		if(ps[p]==i)--p;
	}
	tempn=n,n=tt;
	
	len=sqrt(n)*1.4,block=n/len;
	for(int i=1;i<=block;++i)
		L[i]=R[i-1]+1,R[i]=i*len;
	R[block]=n;
	for(int i=1;i<=block;++i)
	{
		for(int j=L[i];j<=R[i];++j)
		{
			if(j!=L[i])pre[j]=pre[j-1];
			for(int k=1;k<=tot1[a[j]];++k)
				pre[j]+=cnt[i][v1[0][k][a[j]]]*cnt[i][v1[1][k][a[j]]];
			for(int k=1;k<=tot2[a[j]];++k)
				pre[j]+=cnt[i][v2[0][k][a[j]]]*cnt[i][v2[1][k][a[j]]];
			for(int k=1;k<=tot3[a[j]];++k)
				pre[j]+=cnt[i][v3[0][k][a[j]]]*cnt[i][v3[1][k][a[j]]];
			++cnt[i][a[j]],pos[j]=i;
		}
		ans[i][i]=pre[R[i]];
		for(int j=1;j<=maxn;++j)
			cnt[i][j]+=cnt[i-1][j];
		for(int j=R[i];j>=L[i];j--)
		{
			if(j!=R[i])nxt[j]=nxt[j+1];
			for(int k=1;k<=tot1[a[j]];++k)
				nxt[j]+=t[v1[0][k][a[j]]]*t[v1[1][k][a[j]]];
			for(int k=1;k<=tot2[a[j]];++k)
				nxt[j]+=t[v2[0][k][a[j]]]*t[v2[1][k][a[j]]];
			for(int k=1;k<=tot3[a[j]];++k)
				nxt[j]+=t[v3[0][k][a[j]]]*t[v3[1][k][a[j]]];
			++t[a[j]];
		}
		for(int j=L[i];j<=R[i];++j)
			t[a[j]]=0;
	}
	for(int len=2;len<=block;len++)
		for(int l=1;l+len-1<=block;l++)
		{
			int r=l+len-1;
			ans[l][r]=ans[l+1][r]+ans[l][r-1]-ans[l+1][r-1]+cal(l,r);
		}
}
ll query(int l,int r)
{
	l=l_[l],r=r_[r];
	if(l>r)return 0;
	int p=pos[l],q=pos[r];ll res=0;
	if(p==q)
	{
		if(l==L[p])return pre[r];
		res=pre[r]-pre[l-1];
		for(int i=L[p];i<l;++i)
			++t[a[i]];
		for(int i=l;i<=r;++i)
		{
			for(int j=1;j<=tot1[a[i]];++j)
				res-=t[v1[0][j][a[i]]]*t[v1[1][j][a[i]]];
			for(int j=1;j<=tot2[a[i]];++j)
				res-=t[v2[0][j][a[i]]]*t[v2[1][j][a[i]]];
			for(int j=1;j<=tot3[a[i]];++j)
				res-=t[v3[0][j][a[i]]]*t[v3[1][j][a[i]]];
		}
		for(int i=L[p];i<l;++i)
			t[a[i]]=0;
		for(int i=l;i<=r;++i)
			++t[a[i]];
		for(int i=L[p];i<l;++i)
		{
			for(int j=1;j<=tot1[a[i]];++j)
				res-=t[v1[0][j][a[i]]]*t[v1[1][j][a[i]]];
			for(int j=1;j<=tot2[a[i]];++j)
				res-=t[v2[0][j][a[i]]]*t[v2[1][j][a[i]]];
			for(int j=1;j<=tot3[a[i]];++j)
				res-=t[v3[0][j][a[i]]]*t[v3[1][j][a[i]]];
		}
		for(int i=l;i<=r;++i)
			t[a[i]]=0;
		return res;
	}
	res=nxt[l]+pre[r]+ans[p+1][q-1];
	for(int i=l;i<=R[p];++i)
		++t[a[i]];
	for(int i=L[q];i<=r;++i)
	{
		for(int j=1;j<=tot1[a[i]];++j)
		{
			int x=v1[0][j][a[i]],y=v1[1][j][a[i]];
			res+=(t[x]+tt[x])*(cnt[q-1][y]-cnt[p][y])+(t[y]+tt[y])*(cnt[q-1][x]-cnt[p][x])+t[x]*tt[y]+t[y]*tt[x]+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		for(int j=1;j<=tot2[a[i]];++j)
		{
			int x=v2[0][j][a[i]],y=v2[1][j][a[i]];
			res+=(t[x]+tt[x])*(cnt[q-1][y]-cnt[p][y])+(t[y]+tt[y])*(cnt[q-1][x]-cnt[p][x])+t[x]*tt[y]+t[y]*tt[x]+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		for(int j=1;j<=tot3[a[i]];++j)
		{
			int x=v3[0][j][a[i]],y=v3[1][j][a[i]];
			res+=(t[x]+tt[x])*(cnt[q-1][y]-cnt[p][y])+(t[y]+tt[y])*(cnt[q-1][x]-cnt[p][x])+t[x]*tt[y]+t[y]*tt[x]+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		++tt[a[i]];
	}
	for(int i=l;i<=R[p];++i)
		t[a[i]]=0;
	for(int i=L[q];i<=r;++i)
		tt[a[i]]=0,++t[a[i]];
	for(int i=l;i<=R[p];++i)
	{
		for(int j=1;j<=tot1[a[i]];++j)
		{
			int x=v1[0][j][a[i]],y=v1[1][j][a[i]];
			res+=tt[x]*(t[y]+cnt[q-1][y]-cnt[p][y])+tt[y]*(t[x]+cnt[q-1][x]-cnt[p][x])+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		for(int j=1;j<=tot2[a[i]];++j)
		{
			int x=v2[0][j][a[i]],y=v2[1][j][a[i]];
			res+=tt[x]*(t[y]+cnt[q-1][y]-cnt[p][y])+tt[y]*(t[x]+cnt[q-1][x]-cnt[p][x])+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		for(int j=1;j<=tot3[a[i]];++j)
		{
			int x=v3[0][j][a[i]],y=v3[1][j][a[i]];
			res+=tt[x]*(t[y]+cnt[q-1][y]-cnt[p][y])+tt[y]*(t[x]+cnt[q-1][x]-cnt[p][x])+(cnt[q-1][x]-cnt[p][x])*(cnt[q-1][y]-cnt[p][y]);
		}
		++tt[a[i]];
	}
	for(int i=L[q];i<=r;++i)
		t[a[i]]=0;
	for(int i=l;i<=R[p];++i)
		tt[a[i]]=0;
	return res;
}
int main()
{
	freopen("avidity.in","r",stdin);
	freopen("avidity.out","w",stdout);
	input();
	while(m--)
	{
		int l=(lst+read())%tempn+1,r=(lst+read())%tempn+1;
		if(l>r)swap(l,r);
		lst=query(l,r);
		write(lst);
	}
	return 0;
}
