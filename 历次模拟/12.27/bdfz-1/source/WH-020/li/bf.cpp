#include <bits/stdc++.h>
using namespace std;
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
const int N=2e5+5;
/*int n,m,col[N],cnte[N],cntv[N],u[N],v[N];
vector<int>G[N];
void ran(int x,int c){
	col[x]=c;
	for(int y:G[x])if(!col[y])ran(y,c);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		G[u[i]].emplace_back(v[i]);
		G[v[i]].emplace_back(u[i]);
	}
	int idx=0;
	for(int i=1;i<=n;i++)if(!col[i])ran(i,++idx);
	for(int i=1;i<=m;i++){
		cnte[col[u[i]]]++;
	}
	for(int i=1;i<=n;i++)cntv[col[i]]++;
	for(int i=1;i<=idx;i++)assert(cnte[i]+1==cntv[i]),cout<<cnte[i]<<' '<<cntv[i]<<'\n';
	return 0;
}*/

/*

g++ -o bf.exe bf.cpp -O2 -lm -std=c++14 -Wall -Wextra
./bf.exe<li2.in

*/