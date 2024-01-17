#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define ll long long
#define int ll
const int N=2e5+5;
const int M=2e3+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
inl int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inl void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inl void writei(int x){write(x);putchar(' ');}
inl void writel(int x){write(x);putchar('\n');}
int n,t,x,vv,a[N],ans,ma[N],id,res[N],vis[N];
struct ipt{
	int x,v;
	friend bool operator<(ipt a,ipt b){return a.x<b.x;}
}p[N];
struct node{
	int l;
	mutable int r,v;
	int id;
	friend bool operator<(node a,node b){return a.l<b.l;}
}xx[N];
struct Node{
	int v,lid,rid;
	friend bool operator<(Node a,Node b){return a.v<b.v;}
};
inl bool cmp(node a,node b){return a.id<b.id;}
set<node>s;
vector<node>v;
priority_queue<Node>q;
signed main(){
	freopen("distanced.in","r",stdin);
	freopen("distanced.out","w",stdout);
	n=read();t=read();
	auto it=s.begin();
	for(int i=1;i<=n;i++)p[i].x=read();
	for(int i=1;i<=n;i++)p[i].v=read();
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		x=p[i].x;vv=p[i].v;
		if(vv<0)v.push_back((node){x,0,vv,0});
		else{
			if(it==s.end()||x-it->r>t){if(id)xx[id]=*it;it=s.insert((node){x,x,vv,++id}).first;}
			else it->r=x,it->v+=vv;
		}
	}
	xx[id]=*it;
	for(int i=2;i<=id;i++)ma[i]=-inf;
	for(auto i:v){
		auto itr=s.lower_bound(i);
		if(itr==s.end()||itr==s.begin())continue;
		auto itl=itr;itl--;
		if(i.l-itl->r>t||itr->l-i.l>t)continue;
		ma[itr->id]=max(ma[itr->id],i.v);
	}
	for(int i=2;i<=id;i++)q.push((Node){ma[i],i-1,i});
	for(auto i:s)q.push((Node){-i.v,i.id,0});
	for(auto i:s)ans+=i.v;
	for(int i=n;i;i--){
		if(id<=i){res[i]=ans;continue;}
		Node x;
		while(1){
			x=q.top();
			if(!x.rid){
				if(vis[x.lid]){q.pop();continue;}
				vis[x.lid]=1;break;
			}
			else if(vis[x.lid]||vis[x.rid])q.pop();
			else{
				vis[x.lid]=vis[x.rid]=1;
				auto itl=lower_bound(xx+1,xx+id+1,(node){0,0,0,x.lid},cmp);
				auto itr=lower_bound(xx+1,xx+id+1,(node){0,0,0,x.rid},cmp);
				id++;xx[id]=(node){itl->l,itr->r,itl->v+itr->v+x.v,id};
				q.push((Node){-xx[id].v,id,0});
				break;
			}
		}
		res[i]=(ans+=x.v);q.pop();
	}
	for(int i=1;i<=n;i++)writei(res[i]);
	return 0;
}


