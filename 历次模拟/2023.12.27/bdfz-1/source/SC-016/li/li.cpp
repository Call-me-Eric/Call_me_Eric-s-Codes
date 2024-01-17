#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)

#define pb push_back

typedef long long ll;
typedef vector<int>vi;

const int maxn=2e5+10;

vi E[maxn];int deg[maxn];

int par[maxn],vs[maxn],es[maxn];
int find(int x){
  return par[x]==x?x:par[x]=find(par[x]);
}
void unite(int x,int y){
  x=find(x),y=find(y);
  if(x!=y){
    par[x]=y,vs[y]+=vs[x],es[y]+=es[x]+1;
  }else{
    es[y]++;
  }
}

int main(){
  freopen("li.in","r",stdin);
  freopen("li.out","w",stdout);
  ios::sync_with_stdio(0),cin.tie(0);

  int n,m;
  cin>>n>>m;
  rep(i,1,n){
    par[i]=i;
    vs[i]=1;
    es[i]=0;
  }
  rep(i,1,m){
    int u,v;
    cin>>u>>v;
    unite(u,v);
    E[u].pb(v),deg[u]++;
    E[v].pb(u),deg[v]++;    
  }
  ll as0=0;
  bool cir=0;
  rep(i,1,n)if(find(i)==i){
    if(vs[i]==es[i]+1){
      as0+=1ll*vs[i]*es[i]/2;
    }else if(vs[i]==es[i]){
      cir=1;
    }else{
      return puts("-1"),0;
    }
  }
  if(!cir){
    cout<<"0 "<<as0<<endl;
    return 0;
  }
  int as1=n;
  queue<int>Q;
  rep(i,1,n)if(deg[i]==1)Q.push(i),as1--;
  while(!Q.empty()){
    int u=Q.front();
    for(int v:E[u])if(--deg[v]==1){
      Q.push(v),as1--;
    }
  }
  cout<<"1 "<<as1<<endl;
  return 0;
}