#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return rng()%(r-l+1)+l;
}
vector<int>v;
int a[100010];
int main(){
	int cnt=0,sum=0;
	for(int i=1;i<=10;i++){
		for(int S=0;S<(1<<i);S++){
			printf("%d\n",i);
			sum+=i,cnt++;
			for(int j=0;j<i;j++){
				printf("%d ",(S>>j)&1);
			}
			puts("");
		}
	}
	while(sum<500000){
		int n=ran(1,min(500000-sum,100000));
		v.push_back(n),sum+=n;
	}
//	printf("%llu\n",v.size());
	for(int n:v){
		printf("%d\n",n);
//		for(int i=1;i<=n;i+=2) a[i]=a[i+1]=ran(0,(1<<30)-1);
		for(int i=1;i<=n;i++) a[i]=ran(0,1);
		if(rng()&1){
			if(n%2!=0){
				a[1]=1;
				int m=ran(0,(n-1)/2);
				for(int i=1;i<=m;i++) a[i+1]=a[n-i+1]=ran(0,1);
				for(int i=m+2;i<=n-m;i+=2) a[i]=a[i+1]=ran(0,1);
				if(rng()&1) reverse(a+1,a+n+1);
			}
		}
		int j=ran(0,29);
		for(int i=1;i<=n;i++) a[i]<<=j;
		for(int k=0;k<30;k++) if(k^j){
			if(k>j) for(int i=1;i<=n;i++) a[ran(1,n)]^=1<<k,a[ran(1,n)]^=1<<k;
			else for(int i=1;i<=n;i++) a[i]^=1<<k;
		}
		for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
	}
}

