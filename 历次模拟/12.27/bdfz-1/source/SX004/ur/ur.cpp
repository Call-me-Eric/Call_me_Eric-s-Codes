#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n,k,ans=0,an=0;
	cin>>n>>k; 
	if(k==n){
		for(int i=1;i<=n;i++)cout<<'1';
		return 0;
	}
	if(k<=1){
		for(int i=1;i<=n;i++)cout<<'0';
		return 0;
	}
	for(int i=2;i<=n;i++)
		if(!(n%i)){
			int res=k-(k%i);
			if(res>ans)ans=res,an=i;
		}
//	cout<<ans<<' '<<an<<'\n';
	if(!an){
		for(int i=1;i<=n;i++)cout<<'0';
		return 0;
	}
	int x=ans/an,y=n/an;
	while(an--){
		for(int j=1;j<=x;j++)cout<<'1';
		for(int j=x+1;j<=y;j++)cout<<'0';
	}
	return 0;
}
