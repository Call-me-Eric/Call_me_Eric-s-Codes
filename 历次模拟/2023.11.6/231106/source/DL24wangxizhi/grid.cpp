#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e2+10,mod=998244353,inf=0x3f3f3f3f;
inline void Add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
const int dx[5]={0,1,0,-1,0};
const int dy[5]={0,0,-1,0,1};
typedef pair<int,int>pii;
int n,Q,a[maxn][maxn];
int g[maxn][maxn],f[maxn][maxn];
struct Type
{
	int a,x,y;
	friend bool operator <(const Type&A,const Type&B)
	{return A.a<B.a;}
};
inline bool inside(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=n;}
vector<Type>s;
inline void calc(int sx,int sy)
{
	memset(f,0x00,sizeof(f)),memset(g,0x00,sizeof(g)); 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]>=0) f[i][j]=1;
			else g[i][j]=1;
	
	for(auto tmp:s)
	{
		int x=tmp.x,y=tmp.y;
		for(int i=1;i<=4;i++)
		{
			int tx=x+dx[i],ty=y+dy[i];
			if(!inside(tx,ty)) continue; 
			if(a[tx][ty]<=a[x][y]) Add(g[tx][ty],f[x][y]);
			else Add(f[tx][ty],f[x][y]);
		}
	}	
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			Add(ans,f[i][j]),Add(ans,g[i][j]);
	cout<<ans<<'\n';
}
inline void solve()
{
	
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j],s.push_back({a[i][j],i,j});
	sort(s.begin(),s.end());
	cin>>Q;
	for(int i=1,tmp,x,y;i<=Q;i++)
	{
		cin>>x>>y,tmp=a[x][y],a[x][y]=-inf;
		calc(x,y);
		a[x][y]=tmp;
	}
}
signed main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
