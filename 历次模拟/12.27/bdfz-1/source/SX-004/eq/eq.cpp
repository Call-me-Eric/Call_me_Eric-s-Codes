#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=998244353;
int n,Q;
ll a[705][705],b[705][705];
ll ksm(ll x,int y,ll ans=1){
	for(;y;x=x*x%MOD,y>>=1)
		if(y&1)ans=ans*x%MOD;
	return ans;
}
void suan(ll x,ll y){
	if(x==0){
		if(y==0)cout<<"Many\n";
		else cout<<"No\n";
	}
	else cout<<y*ksm(x,MOD-2)<<'\n';
} 
void xiao(){
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)b[i][j]=a[i][j];
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)
			if(b[j][i]){t=j;break;}
		if(!b[t][i])continue;
		for(int j=i;j<=n+1;j++)swap(b[t][j],b[i][j]);
		ll ni=ksm(b[i][i],MOD-2);
		for(int j=1;j<=n;j++){
			if(j==i)continue;
			ll K=b[j][i]*ni%MOD;
//			if((!K)&&b[j][i])cout<<"QWQ"; 
			if(!K)continue; 
			for(int k=i;k<=n+1;k++)
				b[j][k]=(b[j][k]-(K*b[i][k]%MOD)+MOD)%MOD;
		}
	} 
	int op=0;
	for(int i=1;i<=n;i++){
		if(b[i][i]==0){
			if(b[i][n+1]!=0){cout<<"No\n";return;}
			op=1;
		}
		else b[i][n+1]=(b[i][n+1]*ksm(b[i][i],MOD-2))%MOD,b[i][i]=1;
	}
	if(op){cout<<"Many\n";return;}
	for(int i=1;i<=n;i++)cout<<b[i][n+1]<<' ';
	cout<<'\n';
}
int main(){
//	freopen("eq3.in","r",stdin);
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)cin>>a[i][j];
	if(n==1){
		suan(a[1][1],a[1][2]); 
		while(Q--){
			int id,x,y;cin>>id>>x>>y;
			suan(x,y);
		}
	}
	xiao();
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n+1;j++)cout<<b[i][j]<<' ';
//		cout<<'\n';
//	}
	while(Q--){
		int id;cin>>id;
		for(int i=1;i<=n+1;i++)cin>>a[id][i];
		xiao(); 
	}
	return 0;
} 
