#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=15,mod=998244353;
int T,n,m,ans,a[N];
inline int qpow(int b,int p){
	int res=1;b%=mod;
	while(p){
		if(p&1)res=res*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return res;
}
inline int inv(int n){
	return qpow(n,mod-2);
}
void dfs(int stp,int p){
	if(stp==m+1){
		int res=0;
		for(int i=1;i<=n;i++)res+=(a[i]!=i);
		ans+=res*p%mod;ans%=mod;
		return ;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			swap(a[i],a[j]);
			dfs(stp+1,p*inv(n*n)%mod);
			swap(a[i],a[j]);
		}
	}
}
signed main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	T=rd();
	while(T--){
		ans=0;
		n=rd();m=rd();
		for(int i=1;i<=n;i++)a[i]=i;
		dfs(1,1);
		cout<<ans<<endl;
	}
	return 0;
}

