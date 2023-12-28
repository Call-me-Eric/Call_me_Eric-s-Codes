#include <iostream>
using namespace std;
int l,r,d[10],pos,ch[10],cpos;
bool flag;
void dfs(int p)
{
	if(flag==0) return;
	if(p==pos+1)
	{
		int tp=0;
		for (int i=cpos;i;i--) tp=tp*10+d[ch[i]];
		if(tp<2) return;
		for (int i=2;i*i<=tp;i++) if(tp%i==0) return;
		flag=0;
		return;
	}
	ch[++cpos]=p;
	dfs(p+1);
	cpos--;
	dfs(p+1);
}
bool ck(int x)
{
	cpos=pos=0;
	int tp=x;
	while(tp) d[++pos]=tp%10,tp/=10;
	flag=1;
	dfs(1);
	//if(flag) cout<<x<<endl;
	return flag;
}
void solve()
{
	cin>>l>>r;
	int ans=0;
	for (int i=l;i<=r;i++) if(ck(i)) ans++;
	cout<<ans<<endl;
}
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
