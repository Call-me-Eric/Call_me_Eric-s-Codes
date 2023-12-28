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
const int N=2e5+5;
int n,m,col[N],cnte[N],cntv[N],u[N],v[N],deg[N];
vector<int>G[N];
void ran(int x,int c){
	col[x]=c;
	for(int y:G[x])if(!col[y])ran(y,c);
}
int main(){
	freopen("li.in","r",stdin);freopen("li.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		G[u[i]].emplace_back(v[i]);
		G[v[i]].emplace_back(u[i]);
		deg[u[i]]++,deg[v[i]]++;
	}
	int idx=0;
	for(int i=1;i<=n;i++)if(!col[i])ran(i,++idx);
	for(int i=1;i<=m;i++){
		cnte[col[u[i]]]++;
	}
	for(int i=1;i<=n;i++)cntv[col[i]]++;
	for(int i=1;i<=n;i++)if(deg[i]>2){puts("-1");return 0;}
	bool fl=0;
	for(int i=1;i<=idx;i++)if(cntv[i]==cnte[i]){fl=1;break;}
	if(!fl){
		ll ans=0;
		for(int i=1;i<=idx;i++)ans+=(ll)(1+cntv[i])*cntv[i]/2;
		cout<<0<<' '<<ans<<'\n';
		return 0;
	}
	cout<<"1 ";
	ll ans=0;
	for(int i=1;i<=idx;i++)if(cnte[i]==cntv[i])ans+=cntv[i];
	cout<<ans<<'\n';
	return 0;
}



/*

g++ -o li.exe li.cpp -O2 -lm -std=c++14 -Wall -Wextra
./li.exe<li1.in

*/

/*int n,m,e[5005][5005],tmp[5005][5005],a[10000000],b[10000000];
long double f[15],g[15];
int trans(int n,int v[5005][5005],int e[5005][5005]){
	int m=0;
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)if(v[i][j])m++,a[m]=i,b[m]=j;
	if(m<=5000)for(int i=1;i<=m;i++)for(int j=1;j<=m;j++){
		if(i>=j){e[i][j]=e[j][i];continue;}
		if(a[i]==a[j]||a[i]==b[j]||b[i]==a[j]||b[i]==b[j])e[i][j]=1;
		else e[i][j]=0;
	}
	return m;
}
int main(){
	//freopen("li.in","r",stdin);freopen("li.out","w",stdout);
	cin>>n>>m;
	if(n>6){puts("-1");return 0;}
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u][v]=e[v][u]=1;
	}int sum=n;
	f[0]=sum;int lim=0;
	for(int qq=1;qq<=8;qq++){
		n=trans(n,e,tmp);
		sum+=n;lim=qq;cerr<<sum<<'\n';
		f[qq]=sum;if(n>5000)break;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)e[i][j]=tmp[i][j];
	}
	for(int i=0;i<=5;i++){
		for(int j=0;j<=lim;j++){
			g[j]=f[j];
			if(j)for(int k=1;k<=i;k++)g[j]/=j;
		}
		if(g[lim]<=g[lim-1]){cout<<i<<' ',printf("%.0Lf\n",g[lim]);return 0;}
	}
	puts("-1");
}*/

