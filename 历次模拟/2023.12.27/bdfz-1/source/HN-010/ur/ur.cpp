#include<cstdio>
int n,k,i,m,a[7],c[7];
int main(){
	// freopen("ur.in","r",stdin);
	// freopen("ur.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(i=2;i<=n;++i)if(n%i==0){
		while(n%i==0)++c[m],n/=i;
		a[m++]=i;
	}

	return 0;
}