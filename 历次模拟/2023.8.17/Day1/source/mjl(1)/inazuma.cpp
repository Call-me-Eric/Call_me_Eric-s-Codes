#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,M=2e6+5,MDEP=log2(N)+1,inf=(1ll<<60),mod=1e9+7;
inline int read()
{
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return w==1?x:-x;
}
struct edge
{
	int nt,to,v;
}e[N<<1];
int h[N],id;
inline void add(const int x,const int y,const int z){e[++id].to=y;e[id].v=z;e[id].nt=h[x];h[x]=id;}
int n,m,ans=inf;
signed main()
{
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	cin>>n>>m;
	while(m--)
	{
		read();read();
		ans=min(ans,read());
	}
	cout<<ans;
	return 0;
}
/*

*/
