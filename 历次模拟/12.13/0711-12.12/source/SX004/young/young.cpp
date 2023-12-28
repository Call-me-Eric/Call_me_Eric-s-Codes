#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,m,q,k,a[N],b[N],ans=0;
void dfs(int x,int len){
	if(x>k){
		int res=(len==m);
		for(int i=1;res&&i<=len;i++)res&=(a[i]==b[i]);
		return ans+=res,void();
	}
	for(int i=1;i<=len+1;i++){
		if(i==1||a[i]<a[i-1]){
			a[i]++,
			dfs(x+1,max(len,i)),
			a[i]--; 
		}
		if(a[i]>a[i+1]){
			a[i]--;
			dfs(x+1,a[i]?len:i-1);
			a[i]++;
		}
	}
}
int main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)cin>>b[i];
	cin>>q;
	while(q--)cin>>k,ans=0,dfs(1,n),cout<<ans<<'\n';
	return 0;
}
