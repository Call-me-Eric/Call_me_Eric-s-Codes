#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define let const auto
#define pb emplace_back
const int N=1e5+5,mod=998244353;

void add(int &x,const int y){if((x+=y)>=mod) x-=mod;}

int d[N],f[N][2],pow4[N],sum[N],cans[N],pow3[N];
void calc(int n){
	f[0][0]=f[0][1]=1; cans[0]=1;
	for(int i=1; i<=n; i++){
		f[i][0]=pow4[i],f[i][1]=0;
		for(int c:{0,4,6,8}) if(c<=d[i])
			add(f[i][1],f[i-1][c==d[i]]);
		cans[i]=3ll*pow4[i-1]%mod;
	}
	for(int i=1; i<=n+1; i++) sum[i]=(sum[i-1]+f[i-1][0])%mod;
}
int solve1(int n){
	int ans=cans[n];// no 1&9
	add(ans,f[n-1][0]);// 1...
	add(ans,sum[n-1]);// 8001...
	add(ans,sum[n-1]);// 466669.....
	for(int i:{3,4,5,4,5,6,5,6,7,6,7,7,2,4,3,4,3,3,4,5}) if(n>=i) add(ans,f[n-i][0]);
	return ans;
}

int solve2(int n){
	auto getnum = [&](int l,int r){
		int res=0;
		for(int i=r; i>=l; i--) res=res*10+d[i];
		return res;
	};
	int ans=0;
	for(int i:{4,6,8}) if(i<=d[n]) add(ans,f[n-1][i==d[n]]); // no
//	cerr<<"ans = "<<ans<<'\n';
	add(ans,f[n-1][d[n]==1]); //1....
//	cerr<<"ans = "<<ans<<'\n';
	auto calc = [&](int cnt,int val){
		if(n<cnt) return 0;
		int num=getnum(n-cnt+1,n);
		if(val<=num) return f[n-cnt][val==num];
		return 0;
	};
	add(ans,calc(3,649)),add(ans,calc(4,6649)),add(ans,calc(5,66649));
	add(ans,calc(4,6049)),add(ans,calc(5,66049)),add(ans,calc(6,666049));
	add(ans,calc(5,60049)),add(ans,calc(6,600049)),add(ans,calc(7,6000049));
	add(ans,calc(6,660049)),add(ans,calc(7,6660049)),add(ans,calc(7,6600049));
	add(ans,calc(2,91)),add(ans,calc(4,9801)),add(ans,calc(3,901)),add(ans,calc(4,9081));
	add(ans,calc(3,981)),add(ans,calc(3,949)),add(ans,calc(4,9469)),add(ans,calc(5,94669));
//	cerr<<"ans = "<<ans<<'\n';
	if(d[n]>=4){//466669.....
		bool flag=d[n]==4;
		for(int i=n-1; i; i--){
			if(!flag||d[i]==9) add(ans,f[i-1][flag]);
			if(flag&&d[i]<6) break;
			flag&=d[i]==6; 
		}
	}
//	cerr<<"ans = "<<ans<<'\n';
	if(d[n]>=8){//80001.....
		bool flag=d[n]==8;
		for(int i=n-1; i; i--){
			if(!flag||d[i]>=1) add(ans,f[i-1][flag]);
			if(flag&&d[i]<6) break;
			flag&=d[i]==6; 
		}
	}
//	cerr<<"ans = "<<ans<<'\n';
	return ans;
}
char s[N];
int g[N];
int dp(int n,bool up){
	if(!n) return 0;
	if(!up&&g[n]!=-1) return g[n];
	int res=0;
	for(int i:{0,6,9}) if(!up||i<=d[n]){
		add(res,dp(n-1,up&&(i==d[n])));
		if(i==9) add(res,f[n-1][up&&(i==d[n])]);
	}
	if(!up) g[n]=res;
	return res;
}
int solve(bool dec=0){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1; i<=n; i++) d[n-i+1]=s[i]-'0';
	if(dec){
		int pos=1;
		while(!d[pos]) d[pos]=9,pos++;
		d[pos]--;
		while(n>=1&&!d[n]) n--;
	}
	if(!n) return 0;
	calc(n);
	int ans=0;
	for(int i=1; i<n; i++) add(ans,solve1(i));
	add(ans,solve2(n));
	memset(g,-1,sizeof g);
	add(ans,dp(n,1));
	return ans;
}

int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	for(int i=pow4[0]=pow3[0]=1; i<=1e5; i++)
		pow4[i]=4ll*pow4[i-1]%mod,pow3[i]=3ll*pow3[i-1]%mod;
	int T; scanf("%d",&T);
	while(T--){
		int L=solve(1),R=solve();
		printf("%d\n",(R-L+mod)%mod);
	}
}
