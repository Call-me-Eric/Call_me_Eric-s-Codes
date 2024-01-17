#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int mod=1e9+7;
const int inf=1e9;
#define ll long long
#define pb push_back
#define db double
#define ppc __builtin_popcount
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const db pi=acos(-1);
const db eps=1e-6;
int n,m,a[maxn],vis[maxn];db X[maxn],Y[maxn];
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read(),m=read();
	if(m==n){
		for(int i=1;i<=n;i++)putchar('1');puts("");
		return 0;
	}else if(m<=1){
		for(int i=1;i<=n;i++)putchar('0');puts("");
		return 0;
	}
	for(int i=0;i<n;i++)
		X[i]=sin(2*pi/n*i),Y[i]=cos(2*pi/n*i);
	for(int S=0;S<(1<<n);S++){
		db Sx=0,Sy=0;
		for(int i=0;i<n;i++)if(S>>i&1)Sx+=X[i],Sy+=Y[i];
		if(fabs(Sx)<eps&&fabs(Sy)<eps&&!vis[ppc(S)])vis[ppc(S)]=S;
	}for(int i=m;~i;--i)if(vis[i]){
		for(int j=0;j<n;j++)printf("%d",vis[i]>>j&1);
		return 0;
	}
	return 0;
}
