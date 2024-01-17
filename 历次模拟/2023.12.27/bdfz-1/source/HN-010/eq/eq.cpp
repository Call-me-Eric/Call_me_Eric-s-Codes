#include<cstdio>
typedef unsigned long long u64;
const u64 M=998244353;
u64 n,q,i,j,k,a[724][724],b[724][724];
u64 pow(u64 d,u64 u){
	if(!u)return 1;
	u64 r=pow(d,u>>1);
	r*=r;
	if(u&1)(r%=M)*=d;
	return r%M;
}void play(){
	for(i=0;i<n;++i)
	for(j=0;j<=n;++j)b[i][j]=a[i][j];
	bool b2=0;
	for(i=0;i<n;++i){
		if(!b[i][i]){
			for(j=i;j<n&&!b[i][j];++j);
			if(j==n){
				if(b[i][n]){puts("No");return;}
				b2=1;
			}
			for(j=i;j<n&&!b[j][i];++j);
			if(j==n)b2=1;
			for(k=i;k<=n;++k)(b[i][k]+=b[j][k])%=M;
		}u64 d=pow(b[i][i],M-2);
		for(j=i+1;j<n;++j)
		for(k=i+1;k<=n;++k)(b[j][k]+=(M-b[j][i])*d%M*b[i][k])%=M;
	}if(b2){puts("Many");return;}
	for(i=n-1;~i;--i){
		for(j=i+1;j<n;++j)(b[i][n]+=(M-b[i][j])*b[j][n])%=M;
		(b[i][n]*=pow(b[i][i],M-2))%=M;
	}
	for(i=0;i<n;++i)printf("%llu ",b[i][n]);
	puts("");
}int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%llu%llu",&n,&q);
	for(i=0;i<n;++i)
	for(j=0;j<=n;++j)scanf("%llu",a[i]+j);
	play();
	while(q--){
		scanf("%llu",&i);--i;
		for(j=0;j<=n;++j)scanf("%llu",a[i]+j);
		play();
	}return 0;
}