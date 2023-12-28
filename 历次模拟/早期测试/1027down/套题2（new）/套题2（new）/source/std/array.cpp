#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("line: %d\n",__LINE__)
#define ll long long 
using namespace std;

inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+5;
const int inf=1e9;

ll calc(ll w,ll k){//wth seg
	if(w==0) return k*(k+1)/2;
	ll t=w%k,i=w/k,x=calc(i,k);
	return (k*i+t)*(k*k+1)+k*(k+1)/2-t+max(0ll,min(k,i*(k*k+1)+t*k+k-x+1));
}
int cnt;
void work(){
	ll n=read(),k=read();
	ll bel=(n-1)/(k*k+1),V=calc(bel,k);
	if(V==n){
		printf("%lld\n",(bel+1)*(k+1));
		++cnt;
	}
	else{
		ll tot=bel*k+((n-1)%(k*k+1)-(n>V))/k,smaller=bel+(V<n);
		printf("%lld\n",n+tot-smaller);
	}
}

int main()
{
	
  	freopen("array.in","r",stdin);
  	freopen("array.out","w",stdout);
  	
  	int T=read();
  	while(T--) work();
  	debug("cnt=%d\n",cnt);
	return 0;
}
/*
5 1
1 5
3 5
*/ 
