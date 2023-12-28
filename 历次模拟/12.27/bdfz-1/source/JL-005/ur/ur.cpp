#include<bits/stdc++.h>
using namespace std;
int n,k,ans[1000001],cnt,p;
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin>>n>>k;ans[++cnt]=0;
	for(int i=2;i<=n;i++){if(__gcd(i,n)!=1)ans[++cnt]=i;}
	for(int i=1;i<=cnt;i++)if(k<ans[i]){
		p=ans[i-1];break;
	}
	int m=__gcd(p,n),d1=p/m,d2=n/m;
	for(int i=1;i<=n;i++){
		if((i-1)%d2+1<=d1)cout<<1;
		else cout<<0;
	}
	return 0;
}
