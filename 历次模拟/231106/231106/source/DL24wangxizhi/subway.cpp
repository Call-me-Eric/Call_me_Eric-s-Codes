#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e3+10,inf=0x3f3f3f3f3f3f3f3f;
int n,K;
struct subway
{
	int in[maxn],out[maxn],ecnt;
}S[10];
struct Type
{
	int w,x,s,st;
	friend bool operator <(const Type&A,const Type&B)
	{return A.w>B.w;}		
};
vector<pii>e[10][maxn];
int f[510][9][(1<<9)+10];
bool vis[510][9][(1<<9)+10];
inline void solve()
{
	cin>>n>>K;
	for(int k=1;k<=K;k++)
	{
		for(int i=1;i<=n;i++)
			cin>>S[k].in[i];
		for(int i=1;i<=n;i++)
			cin>>S[k].out[i];
		cin>>S[k].ecnt;
		for(int i=1,x,y,z;i<=S[k].ecnt;i++)
			cin>>x>>y>>z,e[k][x].push_back({y,z}),e[k][y].push_back({x,z});
	}
	memset(f,0x3f,sizeof(f));
	priority_queue<Type>q;
	for(int i=1;i<=K;i++) f[1][i][1<<(i-1)]=S[i].in[1],q.push({f[1][i][(1<<i-1)],1,i,1<<(i-1)});
	while(!q.empty())
	{
		Type p=q.top();q.pop();
		int dis=p.w,x=p.x,sub=p.s,st=p.st;
		if(vis[x][sub][st]) continue;
		vis[x][sub][st]=1;
		for(auto edge:e[sub][x])
			if(f[edge.first][sub][st]>dis+edge.second)
			{
				f[edge.first][sub][st]=dis+edge.second;
				q.push({f[edge.first][sub][st],edge.first,sub,st});
			}
		int base=S[sub].out[x];
		
		for(int i=1;i<=K;i++) if(!(st&(1<<(i-1))))
		{
			int nxt=st|(1<<(i-1));
			if(f[x][i][nxt]>dis+base+S[i].in[x])
			{
				f[x][i][nxt]=dis+base+S[i].in[x];
				q.push({f[x][i][nxt],x,i,nxt});
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=K;i++)
		for(int s=0;s<(1<<K);s++)
			ans=min(ans,f[n][i][s]+S[i].out[n]);
	cout<<ans<<endl; 
}
signed main()
{
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
