#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e5+9;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
vector<int>e[N];
int fa[N],op[N],mx[N],sz[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int n=read(),m=read();
	if(n==1){puts("0 1");return 0;}
	if(n==2){puts(m?"0 3":"0 2");return 0;}
	if(n==3){
		if(m==0)puts("0 3");
		if(m==1)puts("0 4");
		if(m==2)puts("0 6");
		if(m==3)puts("1 3");
		return 0;
	}
	rep(i,m){
		int x=read(),y=read();
		e[x].push_back(y);
		mx[x]++;mx[y]++;
	}rep(i,n)sz[i]=1,fa[i]=i;
	rep(x,n)for(int to:e[x]){
		int a=get(x),b=get(to);
		if(a==b){op[a]=1;continue;}
		sz[b]+=sz[a];fa[a]=b;chmx(mx[b],mx[a]);op[b]|=op[a];
	}
	int f=1;rep(i,n)f&=(mx[i]<=2);
	if(f){
		int ans=0;
		rep(i,n)if(fa[i]==i&&op[i])ans+=sz[i];
		if(ans){cout<<1<<" "<<ans<<endl;return 0;}
		rep(i,n)if(fa[i]==i)
			ans+=sz[i]*(sz[i]-1)/2;
		cout<<0<<" "<<ans<<endl;return 0;
	}
	int now=0,ans=0;
	rep(i,n)if(fa[i]==i){
		if(mx[i]>now)now=mx[i],ans=sz[i];
		else if(mx[i]==now)ans+=sz[i];
	}
	cout<<1<<" "<<ans*(now-2)<<endl;
	return 0;
}
