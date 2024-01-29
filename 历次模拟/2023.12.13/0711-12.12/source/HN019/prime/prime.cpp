#include<iostream>
#include<cstdio>
#include<map>
#include<queue>
#define N 7
#define M 105
#define W 1000000
#define K 100002
#define mod 998244353
using namespace std;
int read()
{
    char c=0;
    int sum=0;
    while (c<'0'||c>'9') c=getchar();
    while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
    return sum;
}
void Adder(int &x,int d)
{
    x+=d;
    if (x>=mod) x-=mod;
    return;
}
int T,n,ans,length=1,lengths,depth[M+1],a[N+1],sn[M+1][10],dp[K+1][M+1][2][2],tr[M+1][6];
char sl[K+1],sr[K+1],c[6]={'0','1','4','6','8','9'};
struct reads
{
    bool vis[M+1];
    bool operator < (const reads &t)const
    {
	for (int i=1;i<=length;++i)
	    if (vis[i]!=t.vis[i])
		return vis[i]<t.vis[i];
	return 0;
    }
};
reads sx,tong[M+1];
map<reads,int>p;
queue<reads>q;
bool used[W+1],vis[M+1];
void Insert(string s)
{
    int x=1;
    for (int i=0;i<s.length();++i)
    {
	if (!sn[x][s[i]-'0']) depth[sn[x][s[i]-'0']]=depth[x]+1,sn[x][s[i]-'0']=++length;
	x=sn[x][s[i]-'0'];
    }
    return;
}
void dfs(int x)
{
    if (x==8) return;
    int res,len=x-1;
    bool op=1;
    for (int i=1;i<(1<<len);++i)
    {
	res=0;
	for (int j=1;j<=len;++j)
	    if (i&(1<<(j-1)))
		res=res*10+a[j];
	if (i==(1<<len)-1) op&=(!used[res]);
	else op&=used[res];
    }
    if (op)
    {
	string s;
	for (int i=len;i>=1;--i) s=s+(char)(a[i]+'0');
	Insert(s);
    }
    if (x!=1) a[x]=0,dfs(x+1);
    a[x]=1,dfs(x+1);
    a[x]=4,dfs(x+1);
    a[x]=6,dfs(x+1);
    a[x]=8,dfs(x+1);
    a[x]=9,dfs(x+1);
    return;
}
void bfs()
{
    bool op,opt;
    reads top;
    for (int i=1;i<=length;++i) sx.vis[i]=(i==1);
    tong[++lengths]=sx,p[sx]=lengths,q.push(sx);
    while (!q.empty())
    {
	top=q.front(),q.pop();
	for (int i=0;i<=5;++i)
	{
	    opt=1;
	    for (int j=1;j<=length;++j) vis[j]=top.vis[j];
	    for (int j=length;j>=1;--j)
		if (vis[j])
		    vis[sn[j][c[i]-'0']]=1;
	    for (int j=1;j<=length;++j)
		if (vis[j])
		{
		    op=1;
		    for (int k=0;k<10;++k)
			if (sn[j][k])
			    op=0;
		    if (op)
		    {
			if (depth[j]==1) vis[j]=0;
			else opt=0;
		    }
		}
	    if (opt)
	    {
		for (int k=1;k<=length;++k) sx.vis[k]=vis[k];
		if (p.find(sx)==p.end()) tong[++lengths]=sx,p[sx]=lengths,tr[p[top]][i]=lengths,q.push(sx);
		else tr[p[top]][i]=p[sx];
	    }
	}
    }
    return;
}
int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    string l,r;
    used[0]=used[1]=1;
    for (int i=2;i<=W;++i)
	if (!used[i])
	{
	    for (int j=(i<<1);j<=W;j+=i) used[j]=1;
	}
    dfs(1);
    Insert("94000006");
    Insert("94000066");
    Insert("94000666");
    bfs(),T=read();
    while (T--)
    {
	cin>>l>>r,n=r.length(),ans=0;
	for (int i=1;i<=n;++i) sl[i]=sr[i]='0';
	for (int i=0;i<l.length();++i) sl[i+r.length()-l.length()+1]=l[i];
	for (int i=0;i<r.length();++i) sr[i+1]=r[i];
	for (int i=1;i<=n+1;++i)
	    for (int j=1;j<=lengths;++j)
		for (int op=0;op<=1;++op)
		    for (int op2=0;op2<=1;++op2)
			dp[i][j][op][op2]=0;
	dp[n+1][1][1][1]=1;
	for (int i=n;i>=1;--i)
	    for (int j=1;j<=lengths;++j)
		for (int op=0,opt;op<=1;++op)
		    for (int op2=0,opt2;op2<=1;++op2)
			if (dp[i+1][j][op][op2])
			{
			    for (int k=0;k<=5;++k)
				if (tr[j][k])
				{
				    if (c[k]<sl[i]) opt=0;
				    else if (c[k]>sl[i]) opt=1;
				    else opt=op;
				    if (c[k]<sr[i]) opt2=1;
				    else if (c[k]>sr[i]) opt2=0;
				    else opt2=op2;
				    Adder(dp[i][tr[j][k]][opt][opt2],dp[i+1][j][op][op2]);
				}
			}
	for (int i=1;i<=lengths;++i) Adder(ans,dp[1][i][1][1]);
	printf("%d\n",ans);
    }
    return 0;
}
