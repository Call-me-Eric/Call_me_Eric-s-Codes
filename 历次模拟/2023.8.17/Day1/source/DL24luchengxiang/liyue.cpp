#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
const int N=1e5+5;
int n,qq,len,bl[N],num[N],cnt,a[N],l,r,vis[N];
ll res[N],ans;
struct qus{
	int l,r,id;
	friend bool operator<(qus a,qus b){return bl[a.l]==bl[b.l]?a.r<b.r:bl[a.l]<bl[b.l];}
}q[N];
inl void add(int x){
	for(int i=1;i<=cnt;i++){
		if(num[i]<=x)continue;
		if(num[i]-x>(int)1e5)break;
		ans+=vis[num[i]-x];
	}
	vis[x]++;
}
inl void del(int x){
	vis[x]--;
	for(int i=1;i<=cnt;i++){
		if(num[i]<=x)continue;
		if(num[i]-x>(int)1e5)break;
		ans-=vis[num[i]-x];
	}
}
inl void get_ans(qus q){
	while(l>q.l)add(a[--l]);
	while(r<q.r)add(a[++r]);
	while(l<q.l)del(a[l++]);
	while(r>q.r)del(a[r--]);
	res[q.id]=ans;
}
signed main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	for(int i=1;i*i<=2e5;i++)num[i]=i*i,cnt=i;
	scanf("%d",&n);
	len=sqrt(n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),bl[i]=(i-1)/len+1;
	scanf("%d",&qq);
	for(int i=1;i<=qq;i++){
		scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	}
	sort(q+1,q+qq+1);
	l=1,r=0;
	for(int i=1;i<=qq;i++)get_ans(q[i]);
	for(int i=1;i<=qq;i++)printf("%lld\n",res[i]);
	return 0;
}

