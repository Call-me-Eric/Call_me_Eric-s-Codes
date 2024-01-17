#include "testlib.h"
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define templ template<typename T>
	typedef long long ll;
	typedef double db;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
	templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
	templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
	templ inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifdef NTFOrz
		freopen("a.in","r",stdin);
		#endif
	}
	inline void chktime()
	{
		#ifdef NTFOrz
		cerr<<clock()/1000.0<<'\n';
		#endif
	}
	#ifdef mod
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
	ll inv(ll x){return ksm(x,mod-2);}
	#else
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
	#endif
}
using namespace my_std;

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n=inf.readInt(),m=inf.readInt(),Q=inf.readInt();
    // const int LR[][2]={{1,30},{30,100},{100,300},{300,1000},{1000,3000},{3000,10000},{10000,30000},{30000,100000},{100000,300000},{300000,1000000}};
	// static db sum[233]; static int cc[233];
    // rep(_,1,Q) {
    //     int x=ouf.readInt(),y=ans.readInt();
    //     if (!x&&!y) continue;
    //     if (!x||!y) quitf(_wa, "zero!");
    //     else {
    //         rep(j,0,9) if (y>=LR[j][0]&&y<LR[j][1]) {
    //             sum[j]+=log(1.0*max(x,y)/min(x,y)),++cc[j];
    //         }
    //     }
    // }
    // rep(j,0,9) {
    //     printf("[%d, %d): %.5lf, %d\n",LR[j][0],LR[j][1],exp(sum[j]/cc[j]),cc[j]);
    // }
	db sum=0;
	rep(_,1,Q) {
        int x=ouf.readInt(),y=ans.readInt();
        if (!x&&!y) continue;
        if (!x||!y) quitf(_wa, "zero!");
        else {
			sum+=log(1.0*max(x,y)/min(x,y));
        }
    }
	sum=exp(sum/Q)-1;
	if (sum<=0.2) quitf(_ok, "ok %.3lf", sum);
	quitp(max(0.3,1/(5*sum)), "partial %.3lf", sum);
}