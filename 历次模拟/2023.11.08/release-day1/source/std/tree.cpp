#include <bits/stdc++.h>
#define fo(a,b,c) for (a=b; a<=c; a++)
#define fd(a,b,c) for (a=b; a>=c; a--)
#define ll long long
#define file
using namespace std;

int a[400001][2],ls[200001],len;
int n,m,i,j,k,l;
ll ans,s1,s2;
int mx,mx2;

void New(int x,int y)
{
	++len;
	a[len][0]=y;
	a[len][1]=ls[x];
	ls[x]=len;
}

void dfs(int Fa,int t,int dep)
{
	int i;
	if (dep>mx) mx=dep,mx2=t;
	
	for (i=ls[t]; i; i=a[i][1])
	if (a[i][0]!=Fa)
	dfs(t,a[i][0],dep+1);
}

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&m);
	fo(i,2,n) scanf("%d",&j),New(j,i),New(i,j);
	
	dfs(0,1,1),s2=mx;
	mx=0;
	dfs(0,1,1);
	l=mx2,mx=0;
	dfs(0,l,1);
	s1=mx;
	
	ans=s1+(m-1)*s2*2;
	cout<<ans<<endl;
}