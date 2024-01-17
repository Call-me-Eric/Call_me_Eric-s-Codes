#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=1e6+100;
bool vis[MAXN],a[MAXN];
int n,k,prime[MAXN],dep,pc,sum,tot;
vector<int> d;
int main() {
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	cin>>n>>k;
	for(int i=2;i<=n;i++) {
		if(!vis[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&1ll*i*prime[j]<=1ll*n;j++) {
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	for(int i=1,x=n;i<=tot&&x!=1;i++) {
		while(x%prime[i]==0) d.push_back(prime[i]),x/=prime[i];
	}
	// for(int i=0,nd=d[i];i<d.size()&&nd<=k;i++,nd*=d[i]) {
	// 	if(sum<k/nd*nd) dep=nd,pc=k/nd,sum=k/nd*nd;
	// }
	for(;k;k--) {
		int x=k,nd=1;
		for(int i=0;i<d.size();i++) {
			if(x%d[i]==0) nd*=d[i],x/=d[i];
		}
		if(nd!=1) {
			dep=nd,pc=k/nd,sum=k;
			break;
		}

	}
	if(!dep) {
		for(int i=1;i<=n;i++) cout<<0; cout<<endl;
		return 0;
	}
	else if((n/dep)&1) {
		if(pc&1) a[n/dep/2+1]=1,pc--;
		for(int i=1;pc;i++,pc-=2) a[i]=a[n/dep-i+1]=1;
	} 
	else {
		if(pc&1) {
			a[n/dep/2]=1; pc--;
			for(int i=1;pc;i++,pc-=2) a[i]=a[n/dep-i]=1;
		}
		else for(int i=1;pc;i++,pc-=2) a[i]=a[n/dep-i+1]=1;
	}
	for(int i=1;i<=dep;i++)
		for(int j=1;j<=n/dep;j++)
			cout<<a[j];
	cout<<endl;
	return 0;
}