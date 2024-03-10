#include<bits/stdc++.h>
#define F(i0,i1,i2) for(int i0=i1;i0<=i2;++i0)
#define int long long
#define pii pair<int,int>
#define fr first
#define sc second
using namespace std;
inline int rd(){
	int f=0,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return f?-x:x;
}
const int N=1e5+7;
int lst[N],lsl;
int n,m,a[N],blo[N];
struct Que{
	int l,r,id;
	bool operator<(const Que &_)const{
		return blo[l]==blo[_.l]?r<_.r:l<_.l;
	}
}qe[N];
int tot,cnt[N],ans[N];
void add(int o){
	int x=a[o];
	for(int i=lsl;i>=1;--i){
		if(lst[i]<=x)break;
		int k=lst[i]-x;
		tot+=cnt[k];
	}
	cnt[x]++;
//	cout<<"__"<<o<<' '<<tot<<'\n';
//	F(i,1,n)cout<<cnt[i]<<" ";cout<<'\n';
}
void del(int o){
	int x=a[o];
	cnt[x]--;
	for(int i=lsl;i>=1;--i){
		if(lst[i]<=x)break;
		int k=lst[i]-x;
		tot-=cnt[k];
	}
//	cout<<"__"<<o<<' '<<tot<<'\n';
//	F(i,1,n)cout<<cnt[i]<<" ";cout<<'\n';
}
void solve(){
	int l=1,r=0;
	F(i,1,m){
//		cout<<i<<'\n';
		while(l>qe[i].l)add(--l);
		while(r<qe[i].r)add(++r);
		while(l<qe[i].l)del(l++);
		while(r>qe[i].r)del(r--);
		ans[qe[i].id]=tot;
	}
}
void prew(){
	for(int i=2;i*i<2*n;++i)lst[++lsl]=i*i;
	int len=sqrt(n);
	for(int i=1;i<=n;++i){
		blo[i]=ceil((i*1.0)/len);
	}
//	F(i,1,n)cout<<blo[i]<<" ";
}
signed main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	n=rd();
	F(i,1,n)a[i]=rd();
	prew();
	m=rd();
	F(i,1,m){
		int l=rd(),r=rd();
		qe[i].l=l,qe[i].r=r,qe[i].id=i;
	}
	sort(qe+1,qe+1+m);
	solve();
	F(i,1,m)cout<<ans[i]<<'\n';
	return 0;
}
/*
10
1 2 3 4 5 6 7 8 9 10
*/

