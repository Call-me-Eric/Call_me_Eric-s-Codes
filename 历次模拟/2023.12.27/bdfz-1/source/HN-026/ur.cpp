#include <cstdio>
#include <unordered_set>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
int n,k;
int p[9],rk;
void fac(int x){
	for(int i=2;i<=x;++i){
		if(x%i==0) x/=i,p[++rk]=i;
		while(x%i==0) x/=i;
	}
}
typedef long long ll;
int mx;ll res;
unordered_set<ll> st;
void dfs(ll msk){
	int sz=__builtin_popcountll(msk);
	if(sz>k) return;
	if(st.find(msk)!=st.end()) return;
	st.emplace(msk);
	if(sz>mx){mx=sz;res=msk;}
	for(int i=1;i<=rk;++i){
		int s=n/p[i];
		for(int j=0;j<s;++j){
			ll tmp=0;
			for(int k=0;k<n;k+=s) tmp|=(1ll<<k);
			if(!(tmp&msk)) dfs(tmp|msk);
		}
	}
}
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	n=read();k=read();
	if(k==n){
		for(int i=0;i<n;++i) putchar('1');
		putchar('\n');
		return 0;
	}
	if(k<=1){
		for(int i=0;i<n;++i) putchar('0');
		putchar('\n');
		return 0;
	}
	fac(n);
	if(rk==1){
		while(k%p[1]) --k;
		k/=p[1];
		for(int i=0;i<n;++i)
			if(i%(n/p[1])<k) putchar('1');
			else putchar('0');
		putchar('\n');
		return 0;
	}
	if(rk==2&&p[1]*p[2]==n){
		while((k%p[1])&&(k%p[2])) --k;
		if(!(k%p[1])){
			k/=p[1];
			for(int i=0;i<n;++i)
				if(i%(n/p[1])<k) putchar('1');
				else putchar('0');
			putchar('\n');
			return 0;
		}
		if(!(k%p[2])){
			k/=p[2];
			for(int i=0;i<n;++i)
				if(i%(n/p[2])<k) putchar('1');
				else putchar('0');
			putchar('\n');
			return 0;
		}
		return 0;
	}
	bool ff=0;
	if(n-k<k) k=n-k,ff=1;
	dfs(0);
	if(ff){
		for(int i=0;i<n;++i) putchar((res>>i&1)^49);
	}
	else{
		for(int i=0;i<n;++i) putchar((res>>i&1)^48);
	}
	putchar('\n');
	return 0;
}
