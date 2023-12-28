/*
随便找一棵 DFS 树。设 r 多了，b 少了，g 不知道。
不断寻找 b，加入树中能形成环，把环中的 r 替换掉。可以贪心地换，即对于一条 r，在经过它的 b 中找还没用过且延伸最短的 b 来换。
这样做一遍后，应该要么 r 不多了，要么 b 不少了。然而并不是，可能因为 g 选的不好而无法达成。
b 先替换 r。如果还是不够则尝试替换 g。不可能两个都换不掉，否则无解。
每次选缺的最多的颜色为 b，多的最多的作为 r，不断重复。
会不会 b 换不掉 r，换掉了 g，g 也换不掉 r？好像不会，连续几轮没有成效就无解。
每次换一条即可。O(n^3)。
*/
#include<bits/stdc++.h>
using namespace std;
const int mxlg=12;
struct STTable
{
	struct Value
	{
		int val,id;
		friend bool operator<(Value a,Value b)
		{
			return a.val!=b.val?a.val<b.val:a.id<b.id;
		}
	};
	Value mnv[1100][15];
	int lg2[1100];
	void build(int n,int *val,int *id)
	{
		lg2[1]=0;
		for(int i=2;i<=n;i++)
			lg2[i]=lg2[i-1]+(i==(1<<(lg2[i-1]+1)));
		for(int i=1;i<=n;i++)
			mnv[i][0]=(Value){val[i],id[i]};
		for(int i=1;i<=mxlg;i++)
		{
			for(int j=1;j+(1<<i)-1<=n;j++)
			{
				mnv[j][i]=min<Value>(mnv[j][i-1],mnv[j+(1<<(i-1))][i-1]);
			}
		}
	}
	Value query(int l,int r)
	{
		int x=lg2[r-l+1];
		// cout<<"Query "<<l<<" "<<r<<" x="<<x<<endl;
		return min<Value>(mnv[l][x],mnv[r-(1<<x)+1][x]);
	}
};
int g[260][260],eid[260][260];
bool t[260][260];
int w[4],n,m;
int c[4];
int dep[260],dfi[260],dfo[260],clk;
int elr[1100],edp[1100];
STTable stt;
int cnt[260];
bool ans[32000];
void getTree(int u,int f)
{
	dep[u]=dep[f]+1;
	for(int v=1;v<=n;v++)
	{
		if(dep[v]||!g[u][v])
			continue;
		t[u][v]=t[v][u]=1;
		c[g[u][v]]++;
		getTree(v,u);
	}
}
void prework(int u,int f)
{
	dep[u]=dep[f]+1,dfi[u]=++clk,elr[clk]=u,edp[clk]=dep[u];
	for(int v=1;v<=n;v++)
	{
		if(!t[u][v]||v==f)
			continue;
		prework(v,u);
		++clk,elr[clk]=u,edp[clk]=dep[u];
	}
	dfo[u]=clk;
}
bool under(int u,int v)
{
	// cout<<"Under "<<u<<" "<<v<<" = "<<(dfi[u]<=dfi[v]&&dfo[u]>=dfo[v])<<endl;
	return dfi[u]<=dfi[v]&&dfo[u]>=dfo[v];
}
int lca(int u,int v)
{
	if(dfi[u]>dfi[v])
		swap(u,v);
	// cout<<"Lca "<<u<<" "<<v<<" = "<<stt.query(dfi[u],dfi[v]).id<<endl;
	return stt.query(dfi[u],dfi[v]).id;
}
pair<int,int> fed;
void findEdge(int u,int f,int r,int b)
{
	for(int v=1;v<=n;v++)
	{
		if(!t[u][v]||v==f)
			continue;
		findEdge(v,u,r,b);
		cnt[u]+=cnt[v];
	}
	// cout<<"cnt["<<u<<"]="<<cnt[u]<<endl;
	if(t[u][f]&&g[u][f]==r&&cnt[u]>0)
		fed=make_pair(u,f);
}
void workInit()
{
	memset(dep,0,sizeof(dep));
	memset(dfi,0,sizeof(dfi));
	memset(dfo,0,sizeof(dfo));
	memset(elr,0,sizeof(elr));
	memset(edp,0,sizeof(edp));
	memset(cnt,0,sizeof(cnt));
	fed=make_pair(0,0),clk=0;
}
bool work(int r,int b)
{
	workInit();
	// cout<<"Working r="<<r<<" b="<<b<<" tree :"<<endl;
	// for(int u=1;u<=n;u++)
	// {
	// 	for(int v=u+1;v<=n;v++)
	// 	{
	// 		if(t[u][v])
	// 			cout<<"    "<<u<<" "<<v<<endl;
	// 	}
	// }
	prework(1,0);
	// cout<<"Euler : ";
	// for(int i=1;i<=clk;i++)
	// 	cout<<elr[i]<<" ";
	// cout<<endl;
	stt.build(clk,edp,elr);
	for(int u=1;u<=n;u++)
	{
		for(int v=u+1;v<=n;v++)
		{
			if(g[u][v]==b&&!t[u][v])
			{
				// cout<<"Blue "<<u<<" "<<v<<endl;
				cnt[u]+=1,cnt[v]+=1;
				cnt[lca(u,v)]-=2;
			}
		}
	}
	findEdge(1,0,r,b);
	if(fed.first!=0)
	{
		// cout<<"Found exchangable edge ("<<fed.first<<","<<fed.second<<")"<<endl;
		for(int u=n,flg=0;u>=1;u--)
		{
			for(int v=u+1;v<=n;v++)
			{
				if(!flg&&g[u][v]==b&&(under(fed.first,u)^under(fed.first,v))==1)
				{
					// cout<<"Edge ("<<u<<","<<v<<") exchange ("<<fed.first<<","<<fed.second<<")"<<endl;
					t[u][v]=t[v][u]=1;
					t[fed.first][fed.second]=t[fed.second][fed.first]=0;
					c[r]--,c[b]++;
					flg=1;
				}
			}
		}
		return 1;
	}
	else
		return 0;
}
int main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>w[1]>>w[2]>>w[3]>>m;
	n=w[1]+w[2]+w[3]+1;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		char c;
		cin>>x>>y>>c;
		g[x][y]=g[y][x]=(c=='r'?1:(c=='g'?2:3));
		// assert(eid[x][y]==0&&x!=y);
		eid[x][y]=eid[y][x]=i;
	}
	getTree(1,0);
	int failc=0;
	while(failc<n&&!(c[1]==w[1]&&c[2]==w[2]&&c[3]==w[3]))
	{
		struct Item
		{
			int val,id;
			bool operator<(Item b) const
			{
				return val!=b.val?val<b.val:id<b.id;
			};
		};
		// cout<<"cnt = "<<c[1]<<" "<<c[2]<<" "<<c[3]<<endl;
		Item pr,pb;
		tie(pb,pr)=minmax({(Item){c[1]-w[1],1},(Item){c[2]-w[2],2},(Item){c[3]-w[3],3}});
		int r=pr.id,b=pb.id,g=6-r-b;
		// cout<<"New Round r="<<r<<" b="<<b<<endl;
		if(work(r,b))
			failc=0;
		else
		{
			failc++;
			if(!work(g,b))
			{
				// cout<<"A"<<endl;
				break;
			}
		}
	}
	if(c[1]==w[1]&&c[2]==w[2]&&c[3]==w[3])
	{
		cout<<"YES"<<endl;
		for(int u=1;u<=n;u++)
		{
			for(int v=u+1;v<=n;v++)
			{
				if(t[u][v])
					ans[eid[u][v]]=1;
			}
		}
		for(int i=1;i<=m;i++)
			cout<<ans[i];
		cout<<endl;
	}
	else
		cout<<"NO"<<endl;
}
/*
1 1 3 7
1 2 r
1 4 g
2 3 g
3 4 r
3 5 b
5 6 b
6 2 b
*/