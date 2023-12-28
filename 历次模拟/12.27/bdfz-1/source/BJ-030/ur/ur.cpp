#include<cstdio>
#define TY int
#define MAXN 1000002
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
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
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
}TY n,k,vl,prm[7],nm[7],mx[1<<7],dp[1<<7][MAXN];
TY pct[1<<7],sm[1<<7],ar[MAXN],ct,p,q,fd,S;char ans[MAXN];
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	vl=n=qr();k=qr();mx[0]=1;
	if(n==k){while(n--)putchar('1');return 0;}
	for(TY i=2;i*i<=vl;++i){
		if(vl%i)continue;prm[ct]=sm[1<<ct]=mx[1<<ct]=i;
		nm[ct++]=n/i;while(vl%i==0)vl/=i;
	}if(vl>1){prm[ct]=sm[1<<ct]=mx[1<<ct]=vl;nm[ct++]=n/vl;}S=1<<ct;
	fOR(i,0,S)FOR(j,0,k)dp[i][j]=n+1;dp[0][0]=0;fOR(i,1,S)pct[i]=pct[i>>1]+(1&i);
	fOR(i,3,S){mx[i]=mx[i&-i]*mx[i^(i&-i)];sm[i]=sm[i&-i]+sm[i^(i&-i)];}fOR(i,1,S)mx[i]=n/mx[i];
	fOR(i,0,ct)fOR(j,1<<i,1<<i+1)FOR(x,sm[j],k){
		dp[j][x]=dp[j^(1<<i)][x-prm[i]]/prm[i]+pct[j];
		updmn(dp[j][x],dp[j][x-prm[i]]+1);
		if(dp[j][x]<=mx[j])updmx(fd,x);
	}if(fd==0){while(n--)putchar('0');return 0;}
	fOR(i,0,n)ans[i]='0';
	fOR(i,1,S)if(dp[i][fd]<=mx[i]){
		k=mx[i];ROF(x,ct-1,0)if(i&(1<<x)){
			ar[p++]=x;
			if(dp[i][fd-prm[x]]+1==dp[i][fd])
				{fd-=prm[x++];continue;}
			i^=(1<<x);fd-=prm[x];
		}break;
	}fOR(i,vl=0,p){
		if(i&&ar[i]!=ar[i-1])q=++vl;
		else if(i){
			if(ans[q+=k]=='1')q=++vl;
		}for(TY j=q;j<n;j+=nm[ar[i]])ans[j]='1';
	}printf("%s",ans);return 0;
}
