#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("--line: %d\n",__LINE__)
using namespace std;

const int N=5e5+100;
const int mod=1e9+7;
const int inf=1e9;
inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}

inline ll ksm(ll x,ll k){
	ll res=1;
	while(k){
		if(k&1) res=res*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return res;
}

struct node{
	int ans01,ans10,l1,l2,r1,r2,opl,opr,len;
};
//0:\
//1:/
node operator + (const node &x,const node &y){
	node ans;
	ans.len=x.len+y.len;
	ans.opl=x.opl;
	ans.opr=y.opr;
	ans.l1=(x.l1==x.len&&x.opl==y.opl)?x.l1+y.l1:x.l1;
	ans.l2=(x.l1+x.l2==x.len&&(x.opr==y.opl||x.l2==0))?(x.l1==x.len&&x.opl==y.opl)?x.l2+y.l2:x.l2+y.l1:x.l2;
	ans.r1=(y.r1==y.len&&y.opr==x.opr)?y.r1+x.r1:y.r1;
	ans.r2=(y.r1+y.r2==y.len&&(y.opl==x.opr||y.r2==0))?(y.r1==y.len&&y.opr==x.opr)?y.r2+x.r2:y.r2+x.r1:y.r2;
	ans.ans01=max(x.ans01,y.ans01);
	ans.ans10=max(x.ans10,y.ans10);
	if(x.opr==y.opl){
		if(x.opr==0){//..1100-0011..
			ans.ans10=max(ans.ans10,x.r2+x.r1+y.l1);
			ans.ans01=max(ans.ans01,x.r1+y.l1+y.l2);
		}
		else{//..0011-1100..
			ans.ans01=max(ans.ans01,x.r2+x.r1+y.l1);
			ans.ans10=max(ans.ans10,x.r1+y.l1+y.l2);
		}
	}
	else{
		if(x.opr==0){//..00-11..
			ans.ans01=max(ans.ans01,x.r1+y.l1);
		}
		else{//..11-00..
			ans.ans10=max(ans.ans10,x.r1+y.l1);
		}
	}
	return ans;
}
inline void reverse(node &o){
	swap(o.ans01,o.ans10);
	o.opl^=1;
	o.opr^=1;
}

#define mid ((l+r)>>1)
#define ls (k<<1)
#define rs (k<<1|1)
node tr[N<<2];
bool rev[N<<2];
inline void Rev(int k){
	reverse(tr[k]);
	rev[k]^=1;
}
inline void pushdown(int k){
	if(rev[k]){
		rev[k]=0;
		Rev(ls);
		Rev(rs);
	}
	return;
}
inline void pushup(int k){
	tr[k]=tr[ls]+tr[rs];
	return;
}
char s[N];
int n,m;
void build(int k,int l,int r){
	if(l==r){
		tr[k].ans01=tr[k].ans10=tr[k].l1=tr[k].r1=tr[k].len=1;
		tr[k].l2=tr[k].r2=0;
		tr[k].opl=tr[k].opr=(s[l]=='/');
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k);
}
void change(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		Rev(k);
		return;
	}
	pushdown(k);
	if(x<=mid) change(ls,l,mid,x,y);
	if(y>mid) change(rs,mid+1,r,x,y);
	pushup(k);
	return;
}
node ask(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return tr[k];
	pushdown(k);
	if(y<=mid) return ask(ls,l,mid,x,y);
	if(x>mid) return ask(rs,mid+1,r,x,y);
	return ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y);
}

signed main(){

	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);

	n=read();m=read();
	scanf(" %s",s+1);
	build(1,1,n);
	for(int t=1;t<=m;t++){
		int l=read(),r=read();
		change(1,1,n,l,r);
		node res=ask(1,1,n,l,r);
		printf("%d\n",res.ans01);
	}
	return 0;
}
/*
*/

