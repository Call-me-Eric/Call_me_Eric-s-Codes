#include<bits/stdc++.h>
#define int long long
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=5e5+10;
int n,q;
int a[N],t[N];
namespace sub1{
	int bas,ans[N],curans=0;
	struct query{
		int l,r,id;
		inline bool operator <(const query &o)const{
			return l/bas==o.l/bas?(((o.l/bas)&1)?r<o.r:r>o.r):l<o.l;
		}
	}qry[N];
	void add(int x){
		for(int i=1;i*i<=n*2-1;i++){
			if(i*i>x)curans+=t[i*i-x];
		}
		t[x]++;
	}
	void del(int x){
		t[x]--;
		for(int i=1;i*i<=n*2-1;i++){
			if(i*i>x)curans-=t[i*i-x];
		}
	}
	void work(){
		q=rd();
		for(int i=1;i<=q;i++){
			qry[i].l=rd();qry[i].r=rd();qry[i].id=i;	
		}
		bas=sqrt(n);	
		sort(qry+1,qry+1+q);
//		for(int i=1;i<=q;i++){
//			printf("* %d %d %d\n",qry[i].l,qry[i].r,qry[i].id);
//		}
		int l=0,r=0;
		for(int i=1;i<=q;i++){
			int L=qry[i].l,R=qry[i].r;
			while(l<L)del(a[l++]);
			while(l>L)add(a[--l]);
			while(r<R)add(a[++r]);
			while(r>R)del(a[r--]);
			ans[qry[i].id]=curans;
		}
		for(int i=1;i<=q;i++){
			printf("%lld\n",ans[i]);
		}
	}
}
namespace sub2{
	void work(){
		q=rd();
		while(q--){
			int l=rd(),r=rd(),ans=0;
			for(int i=1;i*i<=r*2-1;i++){
				int lim=ceil(i*i*1.0/2);
				if(lim<l)continue;
				if(lim>r)break;
				ans+=min(r-lim+1,lim-l);
			}
			printf("%lld\n",ans);
		}
	}
}
int s2=1;
signed main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;i++){
		a[i]=rd();if(a[i]!=i)s2=0;
	}
	if(!s2)sub1::work();
	else sub2::work();
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

9
1 2 3 4 5 6 7 8 9
3
1 5
4 7
2 6
*/
