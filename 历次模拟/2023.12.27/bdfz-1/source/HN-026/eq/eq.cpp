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
typedef long long ll;
const int P=998244353;
int qp(int a,int b=P-2){
	int res=1;
	while(b){
		if(b&1) res=(ll)res*a%P;
		a=(ll)a*a%P;b>>=1;
	}
	return res;
}
const int N=705;
int a[N<<1][N],id[N],w[N<<1],s[N],n,q;
int Xmx,Ymx;
void chmx(int &x,int v){if(x<v) x=v;}
void dec(int &x,int v){if((x-=v)<0) x+=P;}
void ins(int p,int lim){
	for(int i=1;i<=n;++i){
		if(!a[p][i]) continue;
		if(!s[i]||w[s[i]]<w[p]){
			int iv=qp(a[p][i]);
			for(int j=i;j<=n+1;++j) a[p][j]=(ll)a[p][j]*iv%P;
			if(s[i]){
				for(int j=i;j<=n+1;++j) dec(a[s[i]][j],a[p][j]);
				swap(p,s[i]);
				if(w[p]<=lim) return;
			}
			else{s[i]=p;return;}
		}
		else{
			int cur=a[p][i];
			for(int j=i;j<=n+1;++j) dec(a[p][j],(ll)a[s[i]][j]*cur%P);
		}
	}
	if(a[p][n+1]) chmx(Ymx,w[p]);
	else chmx(Xmx,w[p]);
}
int res[N];
void qry(int p){
	if(Ymx>p){puts("No");return;}
	if(Xmx>p){puts("Many");return;}
	for(int i=1;i<=n;++i) res[i]=a[s[i]][n+1];
	for(int i=n;i;--i)
		for(int j=1;j<i;++j)
			dec(res[j],(ll)a[s[j]][i]*res[i]%P);
	for(int i=1;i<=n;++i) printf("%d ",res[i]);
	putchar('\n');
}
int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	n=read();q=read();
	for(int i=1;i<=n+q;++i) w[i]=q+1;
	for(int i=1;i<=n;++i){
		id[i]=i;
		for(int j=1;j<=n+1;++j) a[i][j]=read();
	}
	for(int i=1;i<=q;++i){
		int p=read();
		w[id[p]]=i;id[p]=i+n;
		for(int j=1;j<=n+1;++j) a[i+n][j]=read();
	}
	for(int i=1;i<=n;++i) ins(i,0);
	qry(0);
	for(int i=1;i<=q;++i){ins(n+i,i);qry(i);}
	return 0;
}
