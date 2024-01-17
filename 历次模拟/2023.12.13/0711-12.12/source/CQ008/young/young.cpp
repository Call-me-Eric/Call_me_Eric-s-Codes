#include <iostream>
#include <cmath>
using namespace std;
const int maxn=100;
int n,m,a[maxn],b[maxn],q,k,ans,en;
void dfs(int st)
{
	if(st==k)
	{
		if(m!=en) return;
		for (int i=1;i<=m;i++) if(a[i]!=b[i]) return;
		ans++;return;
	}
	int dis=0;
	for (int i=1;i<=max(m,en);i++) dis+=abs(a[i]-b[i]);
	if(dis>k-st) return;
	for (int i=1;i<=en;i++)
	{
		if(i==1||a[i]<a[i-1]) a[i]++,dfs(st+1),a[i]--;
		if(a[i]>a[i+1])
		{
			a[i]--;
			if(i==en&&!a[i]) en--;
			dfs(st+1);
			a[i]++;
			if(en<i) en=i;
		}
	}
	a[++en]++,dfs(st+1),a[en--]--;
}
int main()
{
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	cin>>n;for (int i=1;i<=n;i++) cin>>a[i];
	cin>>m;for (int i=1;i<=m;i++) cin>>b[i];
	cin>>q>>k;
	en=n;
	dfs(0);
	cout<<ans<<endl;
	return 0;
}
