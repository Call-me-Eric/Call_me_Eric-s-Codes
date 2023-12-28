#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace IO {
const int buflen=1<<21;
int x;
bool f;
char ch,buf[buflen],*p1=buf,*p2=buf,obuf[buflen],*p3=obuf;
inline char gc(){return p1==p2&&(p2=buf+fread(p1=buf,1,buflen,stdin),p1==p2)?EOF:*p1++;}
inline void pc(char c){p3-obuf<buflen?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c);}
inline int read(){
	x=0,f=1,ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=gc();
	return f?x:-x;
}
void print(int x){
	if(x/10)print(x/10);
	pc(x%10+48);
}
void PP(){fwrite(obuf,p3-obuf,1,stdout);}
}
using IO::read;
using IO::print;
const int N=705,mod=998244353;
int n,q,a[N][N],b[N][N],val[N];
inline int qp(int a,int b){
	int c=1;for(;b;b>>=1,a=(ll)a*a%mod)if(b&1)c=(ll)c*a%mod;
	return c;
}
void gauss(){
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)b[i][j]=a[i][j];
	for(int i=1;i<=n;i++){
		if(!b[i][i])for(int j=i+1;j<=n;j++)if(b[j][i]){for(int k=1;k<=n+1;k++)swap(b[i][k],b[j][k]);break;}
		const int inv=qp(b[i][i],mod-2);
		for(int j=1;j<=n;j++)if(i!=j){
			const int d=(ll)inv*b[j][i]%mod;
			int k=1;
			for(k=1;k+8<=n+1;k+=8){
				b[j][k]-=(ll)b[i][k]*d%mod,b[j][k]<0&&(b[j][k]+=mod);
				b[j][k+1]-=(ll)b[i][k+1]*d%mod,b[j][k+1]<0&&(b[j][k+1]+=mod);
				b[j][k+2]-=(ll)b[i][k+2]*d%mod,b[j][k+2]<0&&(b[j][k+2]+=mod);
				b[j][k+3]-=(ll)b[i][k+3]*d%mod,b[j][k+3]<0&&(b[j][k+3]+=mod);
				b[j][k+4]-=(ll)b[i][k+4]*d%mod,b[j][k+4]<0&&(b[j][k+4]+=mod);
				b[j][k+5]-=(ll)b[i][k+5]*d%mod,b[j][k+5]<0&&(b[j][k+5]+=mod);
				b[j][k+6]-=(ll)b[i][k+6]*d%mod,b[j][k+6]<0&&(b[j][k+6]+=mod);
				b[j][k+7]-=(ll)b[i][k+7]*d%mod,b[j][k+7]<0&&(b[j][k+7]+=mod);
			}
			for(;k<=n+1;k++){
				b[j][k]-=(ll)b[i][k]*d%mod,b[j][k]<0&&(b[j][k]+=mod);
			}
		}
	}
	//for(int i=1;i<=n;i++,cerr<<'\n')for(int j=1;j<=n+1;j++)cerr<<b[i][j]<<' ';
}
int main(){
	freopen("eq.in","r",stdin);freopen("eq.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)a[i][j]=read();
	gauss();//cerr<<';';
	bool MANY=0,WUJIE=0;
	for(int i=1;i<=n;i++){
		if(b[i][i])val[i]=(ll)qp(b[i][i],mod-2)*b[i][n+1]%mod;
		else if(!b[i][n+1])MANY=1;
		else WUJIE=1;
	}
	if(WUJIE)IO::pc('N'),IO::pc('o'),IO::pc('\n');
	else if(MANY)IO::pc('M'),IO::pc('a'),IO::pc('n'),IO::pc('y'),IO::pc('\n');
	else {
		for(int i=1;i<=n;i++)print(val[i]),IO::pc(' ');IO::pc('\n');
	}
	for(int qq=1,id;qq<=q;qq++){
		id=read();
		for(int i=1;i<=n+1;i++)a[id][i]=read();
		gauss();
		bool MANY=0,WUJIE=0;
		for(int i=1;i<=n;i++){
			if(b[i][i])val[i]=(ll)qp(b[i][i],mod-2)*b[i][n+1]%mod;
			else if(!b[i][n+1])MANY=1;
			else WUJIE=1;
		}
		if(WUJIE)IO::pc('N'),IO::pc('o'),IO::pc('\n');
		else if(MANY)IO::pc('M'),IO::pc('a'),IO::pc('n'),IO::pc('y'),IO::pc('\n');
		else {
			for(int i=1;i<=n;i++)print(val[i]),IO::pc(' ');IO::pc('\n');
		}
	}
	IO::PP();
	return 0;
}

/*

g++ -o eq.exe eq.cpp -O2 -lm -std=c++14 -Wall -Wextra
time ./eq.exe<eq2.in>out2

*/