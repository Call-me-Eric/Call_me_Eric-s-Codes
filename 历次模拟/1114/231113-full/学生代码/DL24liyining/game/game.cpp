#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+5;
int a[maxn],b[maxn];

signed main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n;cin>>n;
	int L,R;cin>>L>>R;
	int s=0;	
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i],s+=a[i];
	sort(b+1,b+n+1);
	int s1=0,s2=0;
	for(int i=1;i<=n;i++)
		if(i%2) s1+=b[i];
	for(int i=n;i;i--)
		if(i%2==0) s2+=b[i];
	if(s2>R||s1<L) cout<<"Alice";
	else cout<<"Bob";
	return 0;
}
