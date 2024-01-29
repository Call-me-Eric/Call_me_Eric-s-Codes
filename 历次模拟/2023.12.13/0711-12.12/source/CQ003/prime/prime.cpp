#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int p=998244353;
const int N=1e5+9;
void chmn(int &x,int y){(x>y)&&(x=y);}
void chmx(int &x,int y){(x<y)&&(x=y);}
int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int T,n;
char s[N];
int dp[N][110][2];
map<vector<int>,int>mp;int idx,to[110][10];
int rt[]={2,3,5,7,11,41,61,19,89,881,991,409,449,499,9001,9049,9649,6949,9949,6469,60649,666649,946669,60000049,66000049,66600049};
vector<int>H[110];
void init(){
	vector<int>B;For(i,0,25)B.push_back(rt[i]);
	queue<vector<int>>q;q.push(B);mp[B]=++idx;
	int all=0;
	while(!q.empty()){
		B=q.front();q.pop();
		For(i,0,9)to[mp[B]][i]=i;
		For(op,0,9){
			vector<int>C;C=B;
			int f=1;
			for(int &x:C)if(x%10==op)x/=10;
			for(int x:C)if(!x)f=0;
			if(f){
				if(!mp[C]){mp[C]=++idx;q.push(C);}
				to[mp[B]][op]=mp[C];
			}else to[mp[B]][op]=0;
		}
		For(i,0,9)if(to[mp[B]][i])H[mp[B]].push_back(i),all++;
	}//cerr<<all<<endl;
}
void upd(int &x,int &y){x+=y;(x>=p)&&(x-=p);}
int work(){
	memset(dp,0,sizeof dp);
	n=strlen(s+1);reverse(s+1,s+1+n);
	//0< 1>
	dp[0][1][0]=1;int qwe;
	rep(i,n)rep(a,105)for(int nt:H[a]){
		qwe=to[a][nt];
		For(op,0,1)upd(dp[i][qwe][nt<s[i]-'0'?0:(nt==s[i]-'0'?op:1)],dp[i-1][a][op]);
	}
	int ans=0;
	rep(a,105)(ans+=dp[n][a][0])%=p;
	return ans;
}
void delL(){
	int n=strlen(s+1);
	int f=(s[1]=='1');
	For(i,2,n)f&=(s[i]=='0');
	if(f){
		rep(i,n-1)s[i]='9';
		s[n]=s[n+1];
	}else{
		f=n;s[f]--;
		while(s[f]=='0'-1){
			s[f]+=9;f--;s[f]--;
		}
	}
}
signed main(){
	//printf("%.5lf\n",(&ppp-&pppp)/1024.0/1024.0);
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init();
	T=read();while(T--){
		int ans=0;
		scanf("%s",s+1);delL();
		ans-=work();
		scanf("%s",s+1);
		ans+=work();
		ans%=p;ans+=p;ans%=p;
		cout<<ans<<endl;
	}
	return 0;
}
/*
449
499
9649
6949
9949
6469
666649
946669
*/
