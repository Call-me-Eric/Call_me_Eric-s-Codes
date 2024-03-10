#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=5005;
int dp[maxn][maxn];
struct node{int a,b,c,d,e,f,id;}q[maxn];

bool check(int x,int y)
{
	if(q[x].a<=q[y].a&&q[x].b<=q[y].b&&q[x].c<=q[y].c&&q[x].d<=q[y].d&&q[x].e<=q[y].e&&q[x].id<=q[y].id) return 1;
	return 0;
} 

signed main()
{
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>q[i].a>>q[i].b>>q[i].c>>q[i].d>>q[i].e>>q[i].f,q[i].id=i;
//	sort(q+1,q+n+1);
//	dp[1][1]=q[1].f;
//	for(int i=1;i<=n;i++)
//		for(int j=1;j<=i;j++) 
//		{
//			if(check(i,j)) dp[i]][j]=max(dp[i][j]+f[x],dp[i][j])
//		}
	for(int i=1;i<=n;i++)
	{
		int ans=0;ans+=q[i].f;
		int nxt=n-1;
		for(int j=n-1;j;j--)
		{
			if(check(nxt,i)) ans+=q[j].f,nxt=j;
		}
		cout<<ans<<endl;
	}
	//I don't know how to do baoli,I am a fool!!!
	//I am sb!!!I don't know how to do DP on a tree,so I can't finish T2,a very easy problem.
	//I don't know how to write DP,so I can't solve T4,what a pity!
	return 0;
}
