#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int fa[maxn];
int x[maxn];
int a[maxn];
int siz[maxn];
vector<int>vec;
int sum;
int n,t,s;
int ans[maxn];
bool cmp(int x,int y){
	return x>y;
}
struct node{
	int x,a,id;
	friend bool operator < (node a,node b){
		return a.x<b.x;
	}
}p[maxn];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main(){
	freopen("distanced.in","r",stdin);
	freopen("distanced.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	for(int i=1;i<=n;i++) fa[i]=i;
	int now=1;
	for(int i=1;i<=n;i++) cin>>p[i].x;
	for(int i=1;i<=n;i++){
		cin>>p[i].a;
		siz[i]=p[i].a;
		p[i].id=i;
	}
	int j=2;
	sort(p+1,p+1+n);
	for(int i=1;i<=n;i++){
		while(j<=n&&abs(p[j].x-p[i].x)<=t){
			int ax=find(p[i].id);
			int bx=find(p[j].id);
			if(ax!=bx){
				fa[bx]=ax;
				if(siz[bx]>0) siz[ax]+=siz[bx];
			}
			j++;
		}
	}
	for(int i=1;i<=n;i++){
		int ax=find(i);
		if(ax==i){
			sum+=siz[ax];
			cout<<siz[ax]<<'\n';
			vec.push_back(siz[ax]);
			s++;
		}
	}
	sort(vec.begin(),vec.end(),cmp);
	for(int i=n;i;i--){
		if(i<s){
			sum-=vec[s-1];
			s--;
			vec.pop_back();
		}
		ans[i]=sum;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}

