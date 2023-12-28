#include<bits/stdc++.h>
using namespace std;
const long long mod=1002772198720536577ll;
map<long long,int>mp[40];
long long cj[40];
int an[1000005];
long long powdv(long long x,long long y){
	long long ans=1;
	while(y){
		if(y&1)ans=(__int128)ans*x%mod;
		y>>=1,x=(__int128)x*x%mod;
	}
	return ans;
}
#define cd complex<double>
cd co[45];
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	if(k==n){
		for(int i=1;i<=n;++i)putchar('1');
		putchar('\n');
		return 0;
	}
	if(k<=1){
		for(int i=1;i<=n;++i)putchar('0');
		putchar('\n');
		return 0;
	}
	if(n<=20){
		double pi=acos(-1);
		co[0]=1;
		cd pp(cos(2*pi/n),sin(2*pi/n));
		for(int i=1;i<=n;++i)co[i]=co[i-1]*pp;
		int wz=-1,zz=0;
		for(int i=0;i<(1<<n);++i)if(__builtin_popcount(i)<=k){
			cd he=0;
			for(int j=1;j<=n;++j)if(i&(1<<(j-1)))he+=co[j-1];
			if(fabs(he.real())>1e-8||fabs(he.imag())>1e-8)continue;
			int bp=__builtin_popcount(i);
			if(wz<bp)wz=bp,zz=i;
		}
		for(int i=1;i<=n;++i)putchar(((zz>>(i-1))&1)+'0');
		putchar('\n');
		return 0;
	}
	for(int i=k;i>=0;--i)if(__gcd(i,n)!=1){
		int z=__gcd(i,n);
		for(int j=0;j<i/z;++j)for(int k=j;k<n;k+=n/z){
			an[k]=1;
		}
		for(int j=0;j<n;++j)putchar(an[j]+'0');
		putchar('\n');
		return 0;
	}
	if(n<=36){
		int n1=n/2,n2=(n+1)/2;
		cj[0]=1;
		long long a1=mod-1,a2=n,a3=__gcd(a1,a2);
		a1/=a3,a2/=a3;
		long long a4=(__int128)a1*a2%(mod-1);
		long long san=powdv(3,a4);
		for(int i=1;i<=n;++i)cj[i]=(__int128)cj[i-1]*san%mod;
		for(int i=0;i<(1<<n2);++i){
			long long he=0;
			for(int j=1;j<=n2;++j)if((i>>(j-1))&1)he=(he+cj[n1+j-1])%mod;
			mp[__builtin_popcount(i)][he]=i;
		}
		int wz=-1;
		for(int i=0;i<(1<<n1);++i){
			long long he=0;
			for(int j=1;j<=n2;++j)if((i>>(j-1))&1)he=(he+cj[j-1])%mod;
			int pb=__builtin_popcount(i);
			if(pb>k)continue;
			int bp=k-pb;
			long long eh=(mod-he)%mod;
			while(bp>=0&&mp[bp].find(eh)==mp[bp].end())--bp;
			if(bp>=0){
				if(wz<bp+pb){
					wz=bp+pb;
					int bh=mp[bp][eh];
					for(int j=1;j<=n1;++j)an[j]=((i>>(j-1)))&1;
					for(int j=1;j<=n2;++j)an[n1+j]=((bh>>(j-1))&1);
				}
			}
		}
		for(int i=1;i<=n;++i)putchar(an[i]+'0');
		putchar('\n');
		return 0;
	}
	return 0;
}
