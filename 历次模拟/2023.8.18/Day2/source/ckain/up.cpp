#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e5+5;

int n, q;
pii a[N], b[N];

inline bool check(pii x, pii y){
	if(x.fr>y.fr || x.sc>y.sc) return 0;
	while(true){
		if(!y.fr || !y.sc) return 0;
		if(y.fr>=y.sc){
			int rp=y.fr;
			y.fr%=y.sc;
			if(y.sc==x.sc && y.fr==x.fr%x.sc && x.fr<=rp) return 1;
		}
		else{
			int rp=y.sc;
			y.sc%=y.fr;
			if(y.fr==x.fr && y.sc==x.sc%x.fr && x.sc<=rp) return 1;
		}
	}
	return 0;
}

signed main(){
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	n=rd(), q=rd();
	for(int i=1; i<=n; i++) a[i]={rd(), rd()};
	for(int i=1; i<=q; i++) b[i]={rd(), rd()};
	for(int i=1; i<=q; i++){
		int ans=0;
		for(int j=1; j<=n; j++) ans+=check(b[i], a[j]);
		printf("%lld\n", ans);
	}
	return 0;
}
