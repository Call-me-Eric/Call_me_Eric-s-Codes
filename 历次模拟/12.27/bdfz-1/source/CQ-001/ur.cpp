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
const int N=1e6+10;
int n,k;
namespace sdp{

const int N=20;
//int f[1<<N];
unordered_map<int,int> f;
queue<int> q;
signed main(){
	vector<int> g;
	For(d,1,n-1)if(n%d==0){
		For(i,0,d-1){
			int S=0;
			For(k,0,n/d-1)S|=(1ll<<(k*d+i));
			g.push_back(S);
		}
	}int ans=0;
	f[0]=1,q.push(0);while(!q.empty()){
		int S=q.front();q.pop();
		int pc=__builtin_popcountll(S);
		if(pc<=k&&pc>__builtin_popcountll(ans))ans=S;
		for(int T:g)if(!(S&T)&&!f[S|T])f[S|T]=1,q.push(S|T);
	}fprintf(stderr,"status count = %lld\n",(int)f.size());
	For(i,0,n-1)putchar((ans>>i&1)?'1':'0');
	return 0;
}

}
int ans[N];
signed main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read(),k=read();
	if(k==n){For(i,1,n)putchar('1');return 0;}
	if(k<=1){For(i,1,n)putchar('0');return 0;}
	vector<int> d;int o=n;
	for(int i=2;i<=o;i++)while(o%i==0)d.push_back(i),o/=i;
	if(d.size()==1){For(i,1,n)putchar('0');return 0;}// Prime
	if(n<=36)return sdp::main();
	if(d.size()==2){
		int p1=d[0],p2=d[1];
		int r1=k%p2,r2=k%p1;
		if(r1<r2){For(i,0,n-1)putchar((i%p1<k/p2)?'1':'0');return 0;}
		else{For(i,0,n-1)putchar((i%p2<k/p1)?'1':'0');return 0;}
	}
	int fl=1;for(int i:d)fl&=i==d.back();
	if(fl){
		int p=d[0],D=n/p;
		For(i,0,k/p-1)For(k,0,n/D-1)ans[k*D+i]=1;
		For(i,0,n-1)printf("%lld",ans[i]);return 0;
	}
	return 0;
}
