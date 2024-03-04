#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=1e5+5;

int n, sqrn, a[N], pos[N], q, ans[N];
vector<pii> qr[N];//{lpos, id}

struct Block{
	int bel[N], lp[N], rp[N], sum[N], v[N];
	inline void init(){
		for(int i=1; i<=n; i++){
			bel[i]=(i-1)/sqrn+1;
			if(!lp[bel[i]]) lp[bel[i]]=i;
			rp[bel[i]]=i;
		}
	}
	inline void upd(int p, int d){
		v[p]+=d;
		sum[bel[p]]+=d;
	}
	inline int que(int l, int r){
		int re=0;
		for(int i=bel[l]+1; i<=bel[r]-1; i++) re+=sum[i];
		for(int i=l; i<=min(rp[bel[l]], r); i++) re+=v[i];
		if(bel[l]!=bel[r]) for(int i=lp[bel[r]]; i<=r; i++) re+=v[i];
		return re;
	}
} bk;

void solve(){
	bk.init();
	for(int i=1; i<=n; i++){
		int lp=sqrt(a[i]); if(lp*lp<=a[i]) lp++;
		for(int j=lp, v; j*j-a[i]<=n; j++){
			v=j*j-a[i];
			if(pos[v]<i) bk.upd(1, 1), bk.upd(pos[v]+1, -1);
		}
		for(pii j: qr[i]) ans[j.sc]=bk.que(1, j.fr);
	}
	for(int i=1; i<=q; i++) printf("%d\n", ans[i]);
}

signed main(){
	freopen("liyue.in", "r", stdin);
	freopen("liyue.out", "w", stdout);
	n=rd(); sqrn=sqrt(n);
	for(int i=1; i<=n; i++) pos[a[i]=rd()]=i;
	q=rd();
	for(int i=1, l, r; i<=q; i++){
		l=rd(), r=rd();
		qr[r].push_back({l, i});
	}
	solve();
	return 0;
}
/*
8
5 7 4 1 8 6 2 3
10
4 5
2 6
1 8
2 7
4 8
3 8
4 7
1 5
2 5
3 7
*/
