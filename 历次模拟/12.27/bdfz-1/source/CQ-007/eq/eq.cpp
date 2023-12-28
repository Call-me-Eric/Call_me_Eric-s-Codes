#include<iostream>
#include<cstdio>
#define rg register
using namespace std;
const int MAXN=810,p=998244353;
int n,q,a[MAXN][MAXN],b[MAXN][MAXN];
int Pow(int x,int k) {
	int ret=1;
	for(rg int i=0;k;i++,x=1ll*x*x%p)
		if(k&(1<<i)) k-=(1<<i),ret=1ll*ret*x%p;
	return ret;
}
int Gauss() {
	int cnt=0;
	for(rg int i=1;i<=n;i++)
		for(rg int j=1;j<=n+1;j++)
			a[i][j]=b[i][j];
	for(rg int i=1;i<=n;i++) {
		bool flag=0;
		for(rg int j=i;j<=n;j++) {
			if(a[j][i]) {
				flag=1,swap(a[i],a[j]);
				break;
			}
		}
		if(!flag) {++cnt; continue;}
		for(rg int j=i,w=Pow(a[i][i],p-2);j<=n+1;j++) a[i][j]=1ll*a[i][j]*w%p;
		for(rg int j=1;j<=n;j++) {
			if(j==i) continue;
			for(rg int k=i,w=a[j][i];k<=n+1;k++) {
				a[j][k]=(1ll*a[j][k]-1ll*a[i][k]*w%p+p)%p;
			}
		}
	}
	for(rg int i=1;i<=n;i++) {
		bool flag=1;
		for(rg int j=1;j<=n;j++) flag&=!a[i][j];
		if(flag&&a[i][n+1]) return -1;
	}
	return cnt;
}
void Output() {
	int tp=Gauss();
	if(tp==-1) printf("No\n");
	else if(tp) printf("Many\n");
	else {
		for(rg int i=1;i<=n;i++) printf("%d ",a[i][n+1]);
		printf("\n");
	}
}
int main() {
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(rg int i=1;i<=n;i++)
		for(rg int j=1;j<=n+1;j++)
			scanf("%d",&b[i][j]);
	Output();
	for(rg int i=1;i<=q;i++) {
		int x; scanf("%d",&x);
		for(rg int i=1;i<=n+1;i++) scanf("%d",&b[x][i]);
		Output();
	}
	return 0;
}