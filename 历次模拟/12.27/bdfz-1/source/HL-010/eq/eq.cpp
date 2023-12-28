#include<cstdio>
#include<cstring>
#include<algorithm>
const int mod=998244353;
using namespace std;
int a[701][702],b[701][702],x[701];
int n;
long long ksm(long long x,int y){
	long long res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void swp(int p,int q){
	int i;
	for(i=1;i<=n+1;i++)swap(b[p][i],b[q][i]);
}
int solve(){
	int i,j,k;
	for(i=1;i<=n;i++)for(j=1;j<=n+1;j++)b[i][j]=a[i][j];
	int nw=0;
	for(i=1;i<=n&&nw<=n;i++){
		nw++;
		int pos=i;
		for(j=i+1;j<=n&&!b[pos][nw];j++)if(b[j][nw])pos=j;
		if(!b[pos][nw]){
			i--;
			continue;
		}
		if(pos!=i)swp(i,pos);
		for(j=i+1;j<=n;j++){
			while(b[j][nw]){
				int x=b[j][nw]/b[i][nw];
				for(k=nw;k<=n+1;k++){
					b[j][k]+=mod-1ll*b[i][k]*x%mod;
					b[j][k]%=mod;
				}
				if(b[j][nw])swp(i,j);
			}
		}
	}
	bool inf=0;
	for(i=n;i;i--){
		long long res=b[i][n+1];
		for(j=n;j>i;j--)res+=mod-1ll*b[i][j]*x[j]%mod,res%=mod;
		if(!b[i][i]){
			if(!res)inf=1;
			else return -1;
		}
		x[i]=res*ksm(b[i][i],mod-2)%mod;
	}
	return inf;
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	int i,j,q;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++){
		for(j=1;j<=n+1;j++)scanf("%d",&a[i][j]);
	}
	int res=solve();
	if(res==-1)printf("No\n");
	if(res==1)printf("Many\n");
	if(!res){
		for(i=1;i<=n;i++)printf("%d ",x[i]);
		printf("\n");
	}
	while(q--){
		int p;
		scanf("%d",&p);
		for(j=1;j<=n+1;j++)scanf("%d",&a[p][j]);
		int res=solve();
		if(res==-1)printf("No\n");
		if(res==1)printf("Many\n");
		if(!res){
			for(i=1;i<=n;i++)printf("%d ",x[i]);
			printf("\n");
		}
	}
}
