#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5;
int n;
int a[maxn];
int block;
struct node{
	int l,r,id;
	friend bool operator < (node a,node b){
		return ((a.l-1)/block==(b.l-1)/block)?a.r<b.r:(a.l-1)/block<(b.l-1)/block;
	}
}p[maxn];
int ans[maxn];
int res=0;
int cnt[maxn];
void add(int x){
	for(int i=1;i<=1001;i++){
		if(i*i<=a[x]) continue;
		if(cnt[i*i-a[x]]>0) res+=cnt[i*i-a[x]];
	}
	cnt[a[x]]++;
	return;
}
void del(int x){
	cnt[a[x]]--;
	for(int i=1;i<=10;i++){
		if(i*i<=a[x]) continue;
		if(cnt[i*i-a[x]]>0){
			res-=cnt[i*i-a[x]];
		}
	}
	return;
}
signed main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	block=sqrt(n);
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>p[i].l>>p[i].r;
		p[i].id=i;
	}
	sort(p+1,p+1+n);
	int ll=0,rr=0;

	for(int i=1;i<=q;i++){
		while(ll<p[i].l){
			del(ll++);
		}
		while(ll>p[i].l){
			add(--ll);
		}
		while(rr<p[i].r){
			add(++rr);
		}
		while(rr>p[i].r){
			del(rr--);
		}
		ans[p[i].id]=res;
	}
	for(int i=1;i<=q;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
}

