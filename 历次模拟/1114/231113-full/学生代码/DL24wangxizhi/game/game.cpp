#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+10;
int L,R,n,a[maxn];
inline void solve()
{
	cin>>n>>L>>R;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	
	int sum=0;
	for(int i=1;i<=n;i+=2) sum+=a[i];
	if(sum<L || sum>R) return cout<<"Alice\n",void(); 
	
	sum=0,reverse(a+1,a+n+1);
	for(int i=1;i<=n;i+=2) sum+=a[i];
	if(sum<L || sum>R) return cout<<"Alice\n",void(); 
	
	cout<<"Bob\n"; 
}
signed main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(NULL);solve();
}
