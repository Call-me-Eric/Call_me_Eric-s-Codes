#include<cstdio>
#include<vector>
#define TY int
#define MAXN 200002
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
}TY n,m,u,v,d[MAXN],to[MAXN][2],nm,ct;
bool vs[MAXN];ll ans;vector<TY>sd[MAXN];
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	n=qr();m=qr();
	FOR(i,1,m){
		u=qr();v=qr();
		sd[u].push_back(i);
		sd[v].push_back(i);
	}FOR(i,1,n){
		if(sd[i].size()>3){printf("-1");return 0;}
		fOR(x,0,sd[i].size())fOR(y,x+1,sd[i].size()){
			if(d[u=sd[i][x]]==2){printf("-1");return 0;}
			if(d[v=sd[i][y]]==2){printf("-1");return 0;}
			to[u][d[u]++]=v;to[v][d[v]++]=u;
		}
	}FOR(i,1,m)if(!d[i])ans+=2;
	FOR(i,1,m)if(!vs[i]&&d[i]){
		vs[i]=true;nm=1;
		for(TY j=to[i][0];j&&!vs[j];++nm){
			vs[j]=true;
			if(vs[to[j][0]])j=to[j][1];
			else j=to[j][0];
		}if(to[i][1]&&vs[to[i][1]]){ct+=nm;continue;}
		for(TY j=to[i][1];j&&!vs[j];++nm){
			vs[j]=true;
			if(vs[to[j][0]])j=to[j][1];
			else j=to[j][0];
		}ans+=1ll*nm*(nm+1);
	}if(ct){printf("1 ");qw(ct);}
	else printf("0 %lld",(ans>>1)+n);
	return 0;
}
