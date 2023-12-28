#include<bits/stdc++.h>
#define int long long
#define N 705
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
const int mod=998244353;
int n,q,a[N][N],b[N][N];
int qpow(int b,int k){int s=1;while(k){if(k&1)s=s*b%mod;b=b*b%mod;k>>=1;}return s;}
void Gauss(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)b[i][j]=a[i][j];
	for(int i=1,p;i<=n;i++){
		for(int j=i;j<=n;j++)if(b[j][i])p=j;
		swap(b[i],b[p]);
		for(int j=1;j<=n;j++)
			if(j!=i){
				int coef=b[j][i]*qpow(b[i][i],mod-2)%mod;
				for(int k=1;k<=n+1;k++)(b[j][k]+=mod-b[i][k]*coef%mod)%=mod;
			}
	}
	/*
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n+1;j++)printf("%lld ",b[i][j]);
	*/
	for(int i=1;i<=n;i++)if(b[i][i]==0&&b[i][n+1])return void(puts("No"));
	for(int i=1;i<=n;i++)if(b[i][i]==0)return void(puts("Many"));
	for(int i=1;i<=n;i++)printf("%lld ",b[i][n+1]*qpow(b[i][i],mod-2)%mod);
	puts("");
}
signed main(){
	file("eq");
	n=read();q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)a[i][j]=read();
	Gauss();
	while(q--){
		int x=read();
		for(int i=1;i<=n+1;i++)a[x][i]=read();
		Gauss();
	}
	return 0;
}
