#include<cstdio>
#define TY int
#define MAXN 10002
#define MAXM 4548
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353,B=12;
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
}char s[MAXN],ban[B][8]={"89","409","449","499","9049","9649","6949","9949","6469","60649","946669","666649"};
TY ln[B]={2,3,3,3,4,4,4,4,4,5,6,6},ml[B],ps[B],now,id[10000000],ct,N=1,T;
TY to[MAXM][5],chg[8][3],dp[MAXN][MAXM],pw[MAXN],ar[MAXN],n,tmp[MAXN][8],ans; 
void dfs(TY now){
	if(id[now])return;id[now]=++ct;bool fl[B],can;TY od=now;
	fOR(i,0,B)if(fl[i]=(ban[i][ps[i]]=='0')){++ps[i];now+=ml[i];}
	can=true;fOR(i,0,B)if(ps[i]==ln[i])can=false;
	if(can){dfs(now);to[id[od]][0]=id[now];}fOR(i,0,B)if(fl[i])--ps[i];now=od;
	fOR(i,0,B)if(fl[i]=(ban[i][ps[i]]=='4')){++ps[i];now+=ml[i];}
	can=true;fOR(i,0,B)if(ps[i]==ln[i])can=false;
	if(can){dfs(now);to[id[od]][1]=id[now];}fOR(i,0,B)if(fl[i])--ps[i];now=od;
	fOR(i,0,B)if(fl[i]=(ban[i][ps[i]]=='6')){++ps[i];now+=ml[i];}
	can=true;fOR(i,0,B)if(ps[i]==ln[i])can=false;
	if(can){dfs(now);to[id[od]][2]=id[now];}fOR(i,0,B)if(fl[i])--ps[i];now=od;
	fOR(i,0,B)if(fl[i]=(ban[i][ps[i]]=='8')){++ps[i];now+=ml[i];}
	can=true;fOR(i,0,B)if(ps[i]==ln[i])can=false;
	if(can){dfs(now);to[id[od]][3]=id[now];}fOR(i,0,B)if(fl[i])--ps[i];now=od;
	fOR(i,0,B)if(fl[i]=(ban[i][ps[i]]=='9')){++ps[i];now+=ml[i];}
	can=true;fOR(i,0,B)if(ps[i]==ln[i])can=false;
	if(can){dfs(now);to[id[od]][4]=id[now];}fOR(i,0,B)if(fl[i])--ps[i];now=od;
}void slv(){
	for(;N<n;++N)FOR(i,1,ct){
		add(dp[N][i],dp[N-1][to[i][0]]);
		add(dp[N][i],dp[N-1][to[i][1]]);
		add(dp[N][i],dp[N-1][to[i][2]]);
		add(dp[N][i],dp[N-1][to[i][3]]);
		add(dp[N][i],dp[N-1][to[i][4]]);
	}FOR(i,now=1,n){
		if(s[i]=='0'){now=to[now][0];continue;}
		add(ans,dp[n-i][to[now][0]]);
		if(s[i]=='4'){now=to[now][1];continue;}
		if(s[i]<'4')break;add(ans,dp[n-i][to[now][1]]);
		if(s[i]=='6'){now=to[now][2];continue;}
		if(s[i]<'6')break;add(ans,dp[n-i][to[now][2]]);
		if(s[i]=='8'){now=to[now][3];continue;}
		if(s[i]<'8')break;add(ans,dp[n-i][to[now][3]]);
		if(s[i]=='9'){now=to[now][4];continue;}break;
	}ar[n+1]=0;ROF(i,n,1){
		if(s[i]=='0'){ar[i]=ar[i+1];continue;}
		ar[i]=pw[n-i];if(s[i]<'4')continue;
		if(s[i]=='4'){add(ar[i],ar[i+1]);continue;}
		add(ar[i],pw[n-i]);if(s[i]<'6')continue;
		if(s[i]=='6'){add(ar[i],ar[i+1]);continue;}
		add(ar[i],pw[n-i]);if(s[i]<'8')continue;
		if(s[i]=='8'){add(ar[i],ar[i+1]);continue;}
		add(ar[i],pw[n-i]);
	}FOR(i,1,n)FOR(j,1,6)tmp[i][j]=0;
	FOR(i,now=1,n){
		FOR(j,1,6){
			add(tmp[i][chg[j][0]],tmp[i-1][j]);
			add(tmp[i][chg[j][1]],tmp[i-1][j]);
			add(tmp[i][chg[j][2]],tmp[i-1][j]);
		}if(!now)continue;
		if(s[i]=='1')add(ans,ar[i+1]);
		else if(s[i]!='0')add(ans,pw[n-i]);
		if(s[i]=='0'){now=chg[now][0];continue;}
		add(tmp[i][chg[now][0]],1);if(s[i]<'8'){now=0;continue;}
		if(s[i]=='8'){now=chg[now][1];continue;}
		add(tmp[i][chg[now][1]],1);now=chg[now][2];
	}FOR(i,2,n)FOR(j,1,6)add(ans,1ll*tmp[i-1][j]*pw[n-i]%M);
}int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	fOR(i,pw[0]=1,MAXN){
		pw[i]=pw[i-1];add(pw[i],pw[i]);add(pw[i],pw[i]);
	}fOR(i,ml[0]=1,B)ml[i]=ml[i-1]*ln[i-1];dfs(0);
	FOR(i,1,ct)dp[0][i]=1;
	chg[1][0]=1;chg[1][1]=6;chg[1][2]=2;
	chg[2][0]=3;chg[2][1]=4;chg[3][1]=5;
	chg[4][0]=5;chg[6][0]=6;
	T=qr();while(T--){
		scanf("%s",s+1);ans=n=0;
		while(s[n+1])++n;slv();ans=M-ans;
		scanf("%s",s+1);n=0;
		while(s[n+1])++n;
		ROF(i,n,1){
			if(s[i]=='9'){s[i]='0';continue;}
			++s[i];break;
		}if(s[1]=='0'){
			s[1]='1';s[++n]='0';
		}slv();qw(ans,'\n');
	}return 0;
}
