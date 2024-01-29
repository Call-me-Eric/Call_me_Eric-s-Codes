#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define ls (x<<1)
#define rs (x<<1|1)
const int maxn = 5e5 + 5, inf = 0x3f3f3f3f;
int n, k, a[maxn], b[maxn];
ll ans;
struct node{int x, y;};
struct tree{
	int ma, mb, la, lb, mn, tg;  
	node va, vb, vc;
}t[maxn << 2];
inline bool operator <(node x, node y){
	return a[x.x] + b[x.y] < a[y.x] + b[y.y];
} 
inline tree operator +(tree x, tree y){
	tree z; z.tg = 0;
	if(a[x.ma] < a[y.ma]) z.ma = x.ma; else z.ma = y.ma;
	if(b[x.mb] < b[y.mb]) z.mb = x.mb; else z.mb = y.mb;
	z.mn = min(x.mn, y.mn);//以上三者直接取最小 
	z.va = min((node){x.ma, y.mb}, min(x.va, y.va));
	z.vc = min((node){y.ma, x.mb}, min(x.vc, y.vc));//在没有特殊限制时，两区间合并可产生新的、符合条件的数对 
	z.vb = min(x.vb, y.vb);
	if(x.mn > y.mn){
	//此时，x所代表的区间内的所有数 都严格大于合并后区间最小值，所以x区间内的数可直接取最小 
		z.vb = min(z.vb, min((node){y.la, x.mb}, x.vc));
		z.la = (a[x.ma] < a[y.la] ? x.ma : y.la), z.lb = y.lb;
		/*z.la=y.la等价于这个前缀直接涵盖了x区间，并与y区间的la前缀接上了*/
	} else if(y.mn > x.mn){
		z.vb = min(z.vb, min((node){y.ma, x.lb}, y.vc));
		z.la = x.la, z.lb = (b[y.mb] < b[x.lb] ? y.mb : x.lb);
	} else{ z.la = x.la, z.lb = y.lb;
		z.vb = min(z.vb, (node){y.la, x.lb});//直接合并前后缀 
	} return z;
}

inline void psd(int x){
	if(!t[x].tg) return;
	t[ls].tg += t[x].tg, t[ls].mn += t[x].tg;
	t[rs].tg += t[x].tg, t[rs].mn += t[x].tg;
	t[x].tg = 0;
}
inline void psp(int x){ t[x] = t[ls] + t[rs];}
inline void build(int x, int l, int r){
	if(l == r) return 
		t[x] = (tree){l, l, l, 0, 0, 0, (node){l, l}, (node){0, 0}, (node){l, l}}, void();
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r), psp(x);
}
inline void updt1(int x, int l, int r, int p){
	if(l == r) return;
	int mid = l + r >> 1; psd(x);
	if(p <= mid) updt1(ls, l, mid, p); else updt1(rs, mid + 1, r, p);
	psp(x);
}
inline void updt2(int x, int l, int r, int L, int R, int p){
	if(l > R or L > r) return;
	if(L <= l and r <= R) {t[x].tg += p, t[x].mn += p; return;}
	int mid = (l + r) >> 1; psd(x);
	updt2(ls, l, mid, L, R, p), updt2(rs, mid + 1, r, L, R, p);
	psp(x);
}

int main(){
	scanf("%d%d", &n, &k); 
	rep(i, 1, n) scanf("%d", &a[i]); rep(i, 1, n) scanf("%d", &b[i]);
	a[0] = b[0] = inf; build(1, 0, n);
	while(k--){ int x, y, p;
		if(t[1].va < t[1].vb) x = t[1].va.x, y = t[1].va.y, p = 1;
		else x = t[1].vb.x, y = t[1].vb.y, p = -1;
        printf("choose 1 :%d %d %d\n",t[1].va.x,t[1].va.y,a[t[1].va.x] + b[t[1].va.y]);
        printf("choose 2 :%d %d %d\n",t[1].vb.x,t[1].vb.y,a[t[1].vb.x] + b[t[1].vb.y]);
		ans += a[x] + b[y]; a[x] = b[y] = inf;
		updt1(1, 0, n, x), updt1(1, 0, n, y);
		updt2(1, 0, n, min(x, y), max(x, y) - 1, p);
	} printf("%lld\n", ans);
	return 0;
} 
