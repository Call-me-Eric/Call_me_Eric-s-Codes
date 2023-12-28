#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int p=998244353;
const int N=710;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n,q;
int a[2*N][N],A[N][N];
int B[N];
int inv(int x,int base=p-2){
	int res=1;
	while(base){
		if(base&1)res=res*x%p;
		x=x*x%p;
		base>>=1;
	}return res;
}
int last[N*2],lastid[N*2];
vector<int>H[N<<2];
void add(int p,int l,int r,int nl,int nr,int i){
	if(nl<=l&&r<=nr){H[p].push_back(i);return;}
	int mid=(l+r)>>1;
	if(mid>=nl)add(p<<1,l,mid,nl,nr,i);
	if(mid<nr)add(p<<1|1,mid+1,r,nl,nr,i);
}
int ans[N];
void output(){
	rep(i,n){
		rep(j,n+1)cout<<A[i][j]<<" ";
		puts("");
	}
}
void solve(int P,int l,int r){
	vector<int>vis;
	int fl=1;
	for(int I:H[P]){
		rep(i,n+1)B[i]=a[I][i];
		int op=0;
		rep(i,n)if(B[i]){
			if(!A[i][i]){
				int del=inv(B[i]);
				For(j,i,n+1)A[i][j]=B[j]*del%p;
				vis.push_back(i);op=1;
				break;
			}
			Rof(j,n+1,i)B[j]=(B[j]+p*p-B[i]*A[i][j])%p;
		}if(!op&&B[n+1]){fl=0;break;}
	}
	if(fl){
		if(l==r){
			rep(i,n)if(!A[i][i]){puts("Many");goto ed;}
			rep(i,n)ans[i]=A[i][n+1];
			Rof(i,n,1)rep(j,i-1)ans[j]=(ans[j]+p*p-A[j][i]*ans[i])%p;
			rep(i,n)printf("%lld ",ans[i]);
			puts("");
			ed:for(int i:vis)memset(A[i],0,sizeof A[i]);
			return;
		}
		int mid=(l+r)>>1;
		solve(P<<1,l,mid);
		solve(P<<1|1,mid+1,r);
	}else For(i,l,r)puts("No");
	for(int i:vis)memset(A[i],0,sizeof A[i]);
}
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read(),q=read();mt19937 R(time(0));
	rep(i,n)rep(j,n+1)a[i][j]=read()%p;
	rep(i,n)lastid[i]=i;
	rep(i,q){
		int x=read();
		rep(j,n+1)a[i+n][j]=read();
		add(1,0,q,last[x],i-1,lastid[x]);
		last[x]=i;lastid[x]=i+n;
	}
	rep(i,n)add(1,0,q,last[i],q,lastid[i]);
	solve(1,0,q);
	return 0;
}
