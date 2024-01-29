#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
bool ST;
const int p=998244353;
int a[22]={11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
string A[22];
bool check(int a,int i){
	// check if b is a subsequence of a
	int j=0,m=A[i].size();
	while(a)if(a%10==(A[i][j]^48)&&++j==m)break;else a/=10;
	return j==m;
}
int n,ans;
bool isprime(int n){
	if(n<=1)return 0;
	for(int i=2;i*i<=n;i++)if(n%i==0)return 0;
	return 1;
}
string NOW;
const int N=5e7;
int all[N],tp;
int flag;
int cnt;
const int M=7e7;
int q[M],head=1,tail=0;
#define push(x) q[++tail]=x
#define top q[head++]
void bfs(){
	head=1,tail=0,push(0);
	while(head<=tail){
		int now=top;
		int fl=1;
		if(now%10==1||now%10==9)For(i,0,21)
			if(now>=a[i]&&a[i]%10==now%10&&check(now,i)){fl=0;break;}
			else if(a[i]>now)break;
		if(fl){
			ans++;
			if(ans==p)ans=0;
			if(flag)all[++tp]=now;
			//if(isprime(now))printf("%d,",now);
		}else continue;
		if(now*10>n)continue;
		for(int i:{0,1,4,6,8,9}){
			int nxt=now*10+i;
			if(nxt>n)break;
			if(nxt>now)push(nxt);
		}
	}
}
int solve(int n){
	::n=n,ans=0;
	//NOW="0",int st=0;dfs(st);
	bfs();
	return ans;
}
int qry(int l,int r){
	return (upper_bound(all+1,all+1+tp,r)-all)-(lower_bound(all+1,all+1+tp,l)-all);
}
bool ED;
signed main(){
	fprintf(stderr,"%.2lf MB\n",abs(&ED-&ST)/1024.0/1024.0);
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	
	For(i,0,21)A[i]=to_string(a[i]),reverse(A[i].begin(),A[i].end());
	flag=1,solve((int)(1e12)),flag=0;
	fprintf(stderr,"Count = %d\n",tp);
	int T=read();
	//int T=1000;
	mt19937 R(time(NULL));int V=1e9;
	while(T--){
		int l=read(),r=read();
		//int l=1,r=1e9;
		//int l=R()%V+1,r=R()%V+1;
		//if(l>r)swap(l,r);
		//assert(qry(l,r)==solve(r)-solve(l-1));
		printf("%lld\n",qry(l,r));
		//printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}
