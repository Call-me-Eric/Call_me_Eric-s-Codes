#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i<(b);++i)
#define rrep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=0;
	while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(f)x=-x;
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
const int N = 5e4 + 5;
const long long mod = 4294967296;
int n,m;
char s[N];
struct Tree{
	long long ans,sum[13];	
	char lz;int tag;
}tr[N<<2];
#define lt (k<<1)
#define rt (k<<1|1)
#define mid ((l+r)>>1)
#define ans(k) k.ans
#define L(k) k.sum[0]
#define l0(k) k.sum[1]
#define l0w(k) k.sum[2]
#define R(k) k.sum[3]
#define Or(k) k.sum[4]
#define w0r(k) k.sum[5]
#define o(k) k.sum[6]
#define Ow(k) k.sum[7]
#define w0(k) k.sum[8]
#define l0w0(k) k.sum[9]
#define Ow0r(k) k.sum[10]
#define Ow0(k) k.sum[11]
#define W(k) k.sum[12]
#define sum(k) tr[k].sum
#define ans(k) k.ans
#define lz(k) k.lz
#define br break
inline Tree pushup(Tree l,Tree r){
	Tree a;
	L(a) = (long long)(L(l) + L(r)) % mod;
	l0(a) = (long long)(l0(l) + l0(r) + L(l) * o(r)) % mod;
	l0w(a) = (long long)(l0w(l) + l0w(r) + L(l) * Ow(r) + l0(l) * W(r)) % mod;
	R(a) = (long long)(R(l) + R(r)) % mod;
	Or(a) = (long long)(Or(l) + Or(r) + o(l) * R(r)) % mod;
	w0r(a) = (long long)(w0r(l) + w0r(r) + W(l) * Or(r) + w0(l) * R(r)) % mod;
	o(a) = (long long)(o(l) + o(r)) % mod;
	Ow(a) = (long long)(Ow(l) + Ow(r) + o(l) * W(r)) % mod;
	w0(a) = (long long)(w0(l) + w0(r) + W(l) * o(r)) % mod;
	l0w0(a) = (long long)(l0w0(l) + l0w0(r) + L(l) * Ow0(r) + l0(l) * w0(r) + l0w(l) * o(r)) % mod;
	Ow0r(a) = (long long)(Ow0r(l) + Ow0r(r) + o(l) * w0r(r) + Ow(l) * Or(r) + Ow0(l) * R(r)) % mod;
	Ow0(a) = (long long)(Ow0(l) + Ow0(r) + o(l) * w0(r) + Ow(l) * o(r)) % mod;
	W(a) = (long long)(W(l) + W(r)) % mod;
	ans(a) = (ans(l) + ans(r) + L(l) * Ow0r(r) + l0(l) * w0r(r) + l0w(l) * Or(r) + l0w0(l) * R(r)) % mod;
//rep(i,0,12)printf("sum[%d]=%lld ",i,a.sum[i]);
//	printf("\nans=%lld\n",a.ans);
	a.tag = -1;
	return a;
}
inline void pushdown(int k,int l,int r){
	if(tr[k].tag == -1)return;
	lz(tr[lt]) = lz(tr[rt]) = lz(tr[k]);
	memset(sum(lt),0,sizeof(sum(lt)));memset(sum(rt),0,sizeof(sum(rt)));
	char x = lz(tr[k]);
	if(x == '(')L(tr[lt])++,L(tr[rt])++;
	if(x == '0')o(tr[lt])++,o(tr[rt])++;
	if(x == 'w')W(tr[lt])++,W(tr[rt])++;
	if(x == ')')R(tr[lt])++,R(tr[rt])++;
	tr[k].tag = -1;
}
void build(int k,int l,int r){
	tr[k].tag = -1;
	if(l == r){
		char x = s[l];
		//printf("l=%d\n",l);
		if(x == '(')L(tr[k])++;
		if(x == '0')o(tr[k])++;
		if(x == 'w')W(tr[k])++;
		if(x == ')')R(tr[k])++;
		return;
	}
	build(lt,l,mid);build(rt,mid+1,r);
	//printf("l=%d r=%d\n",l,r);
	tr[k] = pushup(tr[lt],tr[rt]);
}
void modify(int k,int l,int r,int ll,int rr,char x){
	if(l >= ll && r <= rr){
		memset(sum(k),0,sizeof(sum(k)));
		lz(tr[k]) = x;tr[k].tag = 1;
		if(x == '(')L(tr[k])++;
		if(x == '0')o(tr[k])++;
		if(x == 'w')W(tr[k])++;
		if(x == ')')R(tr[k])++;
		ans(tr[k]) = 0;
		return;
	}
	pushdown(k,l,r);
	if(ll <= mid)modify(lt,l,mid,ll,rr,x);
	if(rr  > mid)modify(rt,mid+1,r,ll,rr,x);
	tr[k] = pushup(tr[lt],tr[rt]);
}
Tree query(int k,int l,int r,int ll,int rr){
	if(l >= ll && r <= rr){
//		puts("return");
//		printf("l=%d r=%d\n",l,r);
//		rep(i,0,12)printf("sum[%d]=%lld ",i,tr[k].sum[i]);
//		printf("\nans=%lld\n",tr[k].ans);
		return tr[k];
	}
	pushdown(k,l,r);
	if(rr <= mid)return query(lt,l,mid,ll,rr);
	if(ll > mid)return query(rt,mid+1,r,ll,rr);
	return pushup(query(lt,l,mid,ll,rr),query(rt,mid+1,r,ll,rr));
}
signed main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	read(n,m);
	scanf("%s",s+1);
	build(1,1,n);
	while(m--){
		char x;
		scanf(" %c ",&x);
		if(x == 'A'){
			int xx;char yy;
			read(xx);
			scanf(" %c ",&yy);
			modify(1,1,n,xx,xx,yy);
		}
		if(x == 'B'){
			int xx,yy;char zz;
			read(xx,yy);scanf(" %c ",&zz);
			modify(1,1,n,xx,yy,zz);	
		}
		if(x == 'C'){
			int xx,yy;
			read(xx,yy);
			Tree Ans = query(1,1,n,xx,yy);
			printf("%lld\n",ans(Ans));	
		}
	}
}

