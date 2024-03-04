#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int root[N];
#define ll long long
struct L{
  ll k,b;
};
ll F(L l,ll x){
  return l.k*x+l.b;
}
int lson[N*30],rson[N*30];
L t[N*30];
ll lazy[N*30];
int opt;
void add(int k,ll x){
  lazy[k]+=x; t[k].b+=x;
}
void pushdown(int k){
  if(!lazy[k]) return;
  if(lson[k]) add(lson[k],lazy[k]);
  if(rson[k]) add(rson[k],lazy[k]);
  lazy[k]=0;
}
void ins(int &k,ll l,ll r,L x){
  if(!k) k=++opt,t[k]=x;
  if(l==r) return;
  pushdown(k);
  ll mid=(l+r)/2;
  if(F(t[k],mid)>F(x,mid)) swap(x,t[k]);
  if(F(t[k],l)>F(x,l)) ins(lson[k],l,mid,x);
  if(F(t[k],r)>F(x,r)) ins(rson[k],mid+1,r,x);
}
ll query(int k,ll l,ll r,ll x){
  if(!k||l>x||r<x) return 1e18;
  if(l==r) return F(t[k],l);
  pushdown(k);
  ll res=F(t[k],x),mid=(l+r)/2;
  if(x<=mid) res=min(res,query(lson[k],l,mid,x));
  else res=min(res,query(rson[k],mid+1,r,x));
  return res;
}
void merge(int &x,int y,ll l,ll r){
  if(!x){
    x=y; return;
  }
  if(!y) return;
  pushdown(x); pushdown(y);
  ll mid=(l+r)/2;
  if(l!=r){
    merge(lson[x],lson[y],l,mid);
    merge(rson[x],rson[y],mid+1,r);
  }
  ins(x,l,r,t[y]);
}
vector<int> v[N];
int a[N];
ll b[N];
void dfs(int u){
  ll sum=0;
  for(auto k:v[u]){
    dfs(k);
    b[k]=query(root[k],1,1e6,a[u]);
    sum+=b[k];
  }
  for(auto k:v[u]){
    add(root[k],sum-b[k]);
    merge(root[u],root[k],1,1e6);
  }
  if(!v[u].size()) ins(root[u],1,1e6,(L){a[u],0});
}
int main(){
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  int n; scanf("%d",&n);
  for(int i=2;i<=n;i++){
    int x; scanf("%d",&x);
    v[x].push_back(i);
  }
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  dfs(1);
  cout<<query(root[1],1,1e6,a[1]);
}
