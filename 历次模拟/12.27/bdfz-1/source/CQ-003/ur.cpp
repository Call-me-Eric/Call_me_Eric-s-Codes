#include<bits/stdc++.h>
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second
#define int long long
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+9;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n,m;
namespace brute{
	unordered_map<int,int>mp;
	vector<int>A,F;
	int a[62][62];
	void dfs(int S){
		if(S&&((S&1)==0))return;
		if(mp[S])return;
		mp[S]=1;F.push_back(S);
		for(int x:A)For(i,0,x-1)
			if((S&a[x][i])==0)dfs(S|a[x][i]);	
	}
	int get(int x){
		int cnt=0;
		while(x)cnt+=x&1,x>>=1;
		return cnt;
	}
	void solve(){
		int x=n;
		rep(i,x-1)if(x%i==0)A.push_back(i);
		for(int x:A)For(i,0,x-1)
			for(int j=i;j<n;j+=x)a[x][i]+=(1ll<<j);
		dfs(0);int ans=0;
		vector<int>H;
		for(int S:F)H.push_back(get(S));
		sort(H.begin(),H.end());H.resize(unique(H.begin(),H.end())-H.begin());
		//for(int x:H)cerr<<x<<" ";puts("");
		for(int S:F)if(get(S)<=m&&get(S)>get(ans))ans=S;
		For(i,0,n-1)cout<<((ans>>i)&1);
	}
}
int ans[N];
bool check(int x){
	For(i,2,x-1)if(x%i==0)return false;
	return true;
}
vector<pi>p;
void SP(int x){
	for(int i=2;i*i<=x;i++)if(x%i==0){
		int cnt=0;
		while(x%i==0)cnt++,x/=i;
		p.push_back(mk(i,cnt));
	}if(x-1)p.push_back(mk(x,1));
}
int dp[N];
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read(),m=read();
	if(m>=n){rep(i,n)putchar('1');exit(0);}
	if(check(n)||m<=1){rep(i,n)putchar('0');exit(0);}
	SP(n);
	if(n<=36){brute::solve();exit(0);}
	if(p.size()==1||p.size()==2&&p[0].se==1&&p[1].se==1){
		int x,y;
		if(p.size()==2){
			x=p[0].fi,y=p[1].fi;
			if(m/x*x<m/y*y)swap(x,y);
		}else x=p[0].fi,y=n/p[0].fi;
		int cnt=0;
		For(i,0,n-1)putchar((i%y<=m/x-1)?(cnt++,'1'):'0');
		//cerr<<cnt<<endl;
		return 0;
	}
	if(p.size()==2){
		int x=p[0].fi,y=p[1].fi;
		int g=n/x/y,op=1;
		dp[0]=1;For(i,x,n)dp[i]|=dp[i-x];For(i,y,n)dp[i]|=dp[i-y];
		if(m*2>n)m=n-m,op=0;
		while(op==1&&!dp[m])m--;
		while(op==0&&!dp[m])m++;
		int a=0,b=0;
		while(m>=x&&dp[m-x])a++,m-=x;
		b=m/y;
		For(k,0,g-1){
			if(a){
				For(i,0,x*y-1)ans[k+i*g]=((i%y<=a-1)?op:1-op);
				a-=y;
				a=max(a,0ll);
			}
			else{
				For(i,0,x*y-1)ans[k+i*g]=((i%x<=b-1)?op:1-op);
				b-=x;
				b=max(b,0ll);
			}
		}assert(a==0&&b==0);
		int cnt=0;
		For(i,0,n-1)cnt+=ans[i];
		//cerr<<cnt<<endl;
		For(i,0,n-1)putchar(ans[i]?'1':'0');
	}
	return 0;
}
