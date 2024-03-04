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
const int mod=1e9+7,N=1e6+10;
int n,m;
int fac[N],inv[N],in[N];
inline int qpow(int b,int p){
	int res=1;
	while(p){
		if(p&1)res=res*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return res;
}
void pre(){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int cnt[N];
signed main(){
	freopen("mondstadt.in","r",stdin);
	freopen("mondstadt.out","w",stdout);
	n=rd();m=rd();
	for(int i=1;i<=m;i++){
		int x=rd(),y=rd();in[y]++;in[x]++;
	}
	pre();
	for(int i=1;i<=n;i++){
		for(int j=2;j<=in[i];j++){
			cnt[j]+=C(in[i],j);
			cnt[j]%=mod;
		}
	}
	int ans=0;
	for(int i=2;i<=n-1;i++){
		ans^=cnt[i];
	}
	cout<<ans<<endl;
	return 0;
}

