#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
int n,q;
const int P=998244353;
typedef long long ll;
int qp(int a,int b=P-2){
	int res=1;
	while(b){
		if(b&1) res=(ll)res*a%P;
		a=(ll)a*a%P;b>>=1;
	}
	return res;
}
const int N=703;
int a[N][N],b[N][N];
void dec(int &x,int v){if((x-=v)<0) x+=P;}
void Gauss(){
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n+1;++j) a[i][j]=b[i][j];
	int c=1;
	for(int i=1;i<=n;++i){
		int p=c;
		while(p<=n&&!a[p][i]) ++p;
		if(p>n) continue;
		if(p!=c){for(int j=i;j<=n+1;++j) swap(a[c][j],a[p][j]);}
		int iv=qp(a[c][i]);
		for(int j=i;j<=n+1;++j) a[c][j]=(ll)a[c][j]*iv%P;
		for(int j=i+1;j<=n;++j){
			int tmp=a[j][i];
			for(int k=i;k<=n+1;++k) dec(a[j][k],(ll)tmp*a[i][k]%P);
		}
		++c;
	}
	if(c<=n){
		for(int i=n;i>=c;--i)
			if(a[i][n+1]){puts("No");return;}
		puts("Many");
		return;
	}
	for(int i=n;i;--i)
		for(int j=i-1;j;--j)
			dec(a[j][n+1],(ll)a[i][n+1]*a[j][i]%P);
	for(int i=1;i<=n;++i) printf("%d ",a[i][n+1]);
	putchar('\n');
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.ans","w",stdout);
	n=read();q=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n+1;++j) b[i][j]=read();
	Gauss();
	while(q--){
		int p=read();
		for(int i=1;i<=n+1;++i) b[p][i]=read();
		Gauss();
	}
	return 0;
}
