#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=(i1);i0<=(i2);++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=1e5+7,mod=998244353;
int Pow(int a,int b){int ans=1;for(;b;b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;return ans;}
signed main(){
	freopen("poster.in","r",stdin);
	freopen("poster.out","w",stdout);
	int T=rd();
	while(T--){
		int n=rd(),m=rd();
		if(n==1||m==0){
			cout<<0<<'\n';
			continue;
		}
		int mu=Pow(n,m);
		int zi=4*(1+m*n%mod)%mod*m%mod*Pow(2,mod-2)%mod;
		cout<<zi*Pow(mu,mod-2)%mod<<'\n';	
	}
	
	return 0;
}


