#include <iostream>
using namespace std;
const int maxn=255;
struct L{
	int u,v,bro,id;
}li[maxn];
int n,r,g,b,m,mo[maxn];
int head[maxn],cnt,isc[maxn],vis[maxn];
bool comp;
void add(int u,int v,int id)
{
	li[++cnt]=(L){u,v,head[u],id};
	head[u]=cnt;
}
void dfsc(int u)
{
	vis[u]=1;
	for (int i=head[u];i;i=li[i].bro)
	{
		int v=li[i].v;
		if(vis[v]||!isc[li[i].id]) continue;
		dfsc(v);
	}
}
void dfs(int pos,int ch)
{
	if(comp) return;
	if(pos==m+1)
	{
		if(ch!=n-1)return;
		int chk[4]={0,0,0,0};
		for (int i=1;i<=m;i++)
		{
			if(isc[i]) chk[mo[i]]++;
		}
		if(chk[1]!=r||chk[2]!=g||chk[3]!=b) return;
		for (int i=1;i<=n;i++) vis[i]=0;
		dfsc(1);
		for (int i=1;i<=n;i++) if(!vis[i]) return;
		comp=1;
		cout<<"YES"<<endl;
		for (int i=1;i<=m;i++) cout<<(isc[i]?"1":"0");
		cout<<endl;
		return;
	}
	if(ch>n-1) return;
	dfs(pos+1,ch);
	isc[pos]=1;
	dfs(pos+1,ch+1);
	isc[pos]=0;
}
int main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin>>r>>g>>b>>m;
	n=r+g+b+1;
	if(n>7)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	for (int i=1;i<=m;i++)
	{
		int u,v;char c;
		cin>>u>>v>>c;
		if(c=='r') mo[i]=1;
		if(c=='g') mo[i]=2;
		if(c=='b') mo[i]=3;
		add(u,v,i);add(v,u,i);
	}
	dfs(1,0);
	if(!comp) cout<<"NO"<<endl;
	return 0;
}
