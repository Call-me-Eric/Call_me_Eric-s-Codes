#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e3+5;
int n,q;
int a[maxn];
struct node{
	int l,r;
}p[maxn];
int f[maxn][maxn];
int sum[maxn][maxn];
int anss[maxn][maxn];
int maxx;
#define getchar() cin.get()
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
signed main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	n=read();
	q=read();
	for(int i=1;i<=n;i=-~i){
		a[i]=read();
		if(!p[a[i]].l) p[a[i]].l=i;
		else p[a[i]].l=min(i,p[a[i]].l);
		if(!p[a[i]].r) p[a[i]].r=i;
		else p[a[i]].r=max(i,p[a[i]].r);
	}
	for(int i=1;i<=n;i=-~i){
		if(p[a[i]].l==p[a[i]].r) f[i][i]=a[i],sum[i][i]+=a[i];
		for(int j=i+1;j<=n;j=-~j){
			if(p[a[j]].l>=i&&p[a[j]].r<=j) f[i][j]=max(f[i][j-1],a[j]);
			else f[i][j]=f[i][j-1];
			sum[i][j]=sum[i][j-1]+f[i][j];
		}
	}
	for(int i=1;i<=n;i=-~i){
		for(int j=1;j<=n;j=-~j){
			anss[i][j]=-1;
		}
	}
	for(int i=1;i<=q;i=-~i){
		int l,r;
		l=read();
		r=read();
		int ans=0;
		if(anss[l][r]!=-1){
			cout<<anss[l][r]<<'\n';
			continue;
		}
		for(int j=l;j<=r;j=-~j){
			ans+=sum[j][r];
		}
		anss[l][r]=ans;
		cout<<ans<<'\n';
	}
	return 0;
}

