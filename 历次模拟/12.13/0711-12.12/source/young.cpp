#include<bits/stdc++.h>
using namespace std;
int a[50],n,m,b[50],q,k,summ,p;long long ans=0;
void dfs(int x,int sum){
	if(x==k){
		if(sum!=summ)return;
		for(int i=1;i<=max(n,m)+10;i++)if(a[i]!=b[i])return;
		ans++;return;
	}
	for(int i=1;i<=n+10;i++){
		if(a[i]!=a[i-1]||i==1){a[i]++,dfs(x+1,sum+1),a[i]--;}
		if(a[i]!=0&&a[i]!=a[i+1])a[i]--,dfs(x+1,sum-1),a[i]++;
	}
}
int main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	cin>>n;for(int i=1;i<=n;i++)scanf("%d",&a[i]),p+=a[i];
	cin>>m;for(int i=1;i<=m;i++)scanf("%d",&b[i]),summ+=b[i];
	cin>>q>>k;dfs(0,p);cout<<ans;
	return 0;
}
