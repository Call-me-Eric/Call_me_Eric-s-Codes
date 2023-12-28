//Code by juju527.
#include<bits/stdc++.h>
typedef long long ll;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector<int>
#define eb emplace_back
using namespace std;
const int maxn=705,mod=998244353;
int n;
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
inline int add(int x){return (x>=mod)?x-mod:x;}
inline int sub(int x){return (x<0)?x+mod:x;}
inline int power(int x,int b){
	int res=1;
	while(b){
		if(b&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		b>>=1;
	}
	return res;
}
int nxt[maxn];
int a[2*maxn][maxn],pos[maxn],c[2*maxn];
int p[maxn][maxn],id[maxn];
int mx1,mx2;
void ins(int *buf,int c){
	for(int i=1;i<=n;i++){
		if(!buf[i])continue;
		if(!p[i][i]){
			for(int j=i;j<=n+1;j++)p[i][j]=buf[j];
			id[i]=c;
			return ;
		}
		if(c>id[i]){
			for(int j=i;j<=n+1;j++)swap(p[i][j],buf[j]);
			swap(id[i],c);
		}
		int v=1ll*buf[i]*power(p[i][i],mod-2)%mod;
		for(int j=i;j<=n+1;j++)buf[j]=sub(buf[j]-1ll*v*p[i][j]%mod);
	}
	if(!buf[n+1])mx1=max(mx1,c);else mx2=max(mx2,c);
	return ;
}
int iv[maxn],res[maxn];
void solve(int lim){
	if(mx2>lim){puts("No");return ;}
	if(mx1>lim){puts("Many");return ;}
	for(int i=1;i<=n;i++)res[i]=1ll*(iv[i]=power(p[i][i],mod-2))*p[i][n+1]%mod;
	for(int i=n;i>=1;i--)
		for(int j=1;j<i;j++)
			if(p[j][i])
				res[j]=sub(res[j]-1ll*p[j][i]*iv[j]%mod*res[i]%mod);
	for(int i=1;i<=n;i++){
		printf("%d",res[i]);
		if(i<n)putchar(' ');
	}
	puts("");
	return ;
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	int q;
	n=read(),q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			a[i][j]=read();
	for(int i=1;i<=q;i++){
		pos[i]=read();
		for(int j=1;j<=n+1;j++)a[n+i][j]=read();
	}
	for(int i=1;i<=n;i++)nxt[i]=q+1;
	for(int i=q;i>=1;i--){
		c[n+i]=nxt[pos[i]];
		nxt[pos[i]]=i;
	}
	for(int i=1;i<=n;i++)c[i]=nxt[i];
	for(int i=1;i<=n;i++)ins(a[i],c[i]);
	solve(0);
	for(int i=1;i<=q;i++)ins(a[n+i],c[n+i]),solve(i);
	return 0;
}
