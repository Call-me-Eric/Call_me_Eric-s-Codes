#include <bits/stdc++.h>
using namespace std;

unsigned long long
Solve(int a,int b){
	// hello :)
	return 0;
}

int main(){
	int n,T,seed1,seed2,p;
	unsigned long long ans=0,res=0;
	scanf("%d %d %d %d %d",&n,&T,&seed1,&seed2,&p);
	for (int i=1;i<=n;i++){
		int a,b; 
		if (i<=T) scanf("%d %d",&a,&b);
		else a=(1ll*ans*i^seed1)%p+1, b=(1ll*ans*i^seed2)%p+1;
		res=Solve(a,b);
		ans=(ans^(1ll*res*i));
	}
	printf("%llu",ans);
	return 0;
}
