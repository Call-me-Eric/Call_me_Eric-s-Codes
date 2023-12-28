#include<cstdio>
#include<vector>
#define TY ll
#define MAXN 704
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void Add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n,m,a[MAXN<<1][MAXN],b[MAXN],l,r,k;vector<TY>vec[MAXN],tre[MAXN<<2];
struct node{TY sq[MAXN][MAXN],ps[MAXN],sz;}ar[10],zro;
void add(node &x,TY id){
	FOR(i,0,n)b[i]=a[id][i];
	fOR(i,0,n)if(b[i]){
		if(~x.ps[i]){
			ROF(j,n,i)Add(b[j],M-b[i]*x.sq[x.ps[i]][j]%M);continue;
		}k=qp(b[i],M-2);FOR(j,i,n)x.sq[x.sz][j]=b[j]*k%M;
		x.ps[i]=x.sz++;return;
	}if(b[n])x.sz=-1;
}void print(node &a){
	if(a.sz<n){printf("Many\n");return;}
	ROF(i,n-1,1){
		l=a.ps[i];ROF(j,i-1,0)Add(a.sq[a.ps[j]][n],M-a.sq[l][n]*a.sq[a.ps[j]][i]%M);
	}fOR(i,0,n)qw(a.sq[a.ps[i]][n],' ');putchar('\n');
}void ins(TY i,TY j,TY id){
	if(l<=i&&j<=r){tre[id].push_back(k);return;}
	TY mid=i+j>>1;if(l<=mid)ins(i,mid,id<<1);
	if(r>mid)ins(mid+1,j,id<<1|1);
}void findans(TY i,TY j,TY id,TY d){
	fOR(x,0,tre[id].size()){
		add(ar[d],tre[id][x]);
		if(ar[d].sz==-1){
			FOR(_,i,j)printf("No\n");return;
		}
	}if(i==j){print(ar[d]);return;}TY mid=i+j>>1;
	ar[d+1]=ar[d];findans(i,mid,id<<1,d+1);
	ar[d+1]=ar[d];findans(mid+1,j,id<<1|1,d+1);
}int main(){
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	fOR(i,0,MAXN)zro.ps[i]=-1;
	fOR(i,0,10)ar[i]=zro;
	n=qr();m=qr();
	FOR(i,1,n)FOR(j,0,n)a[i][j]=qr();
	FOR(i,1,m){
		vec[qr()].push_back(i);
		FOR(j,0,n)a[n+i][j]=qr();
	}FOR(i,1,n){
		if(vec[i].empty()){
			tre[1].push_back(i);continue;
		}l=0;r=vec[i].front()-1;k=i;ins(0,m,1);
		fOR(j,1,vec[i].size()){
			l=r+1;r=vec[i][j]-1;
			k=vec[i][j-1]+n;ins(0,m,1);
		}l=r+1;r=m;k=vec[i].back()+n;ins(0,m,1);
	}findans(0,m,1,0);return 0;
}
