#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)

int main(){
  freopen("rgb.in","r",stdin);
  freopen("rgb.out","w",stdout);
  int n[3],m;
  cin>>n[0]>>n[1]>>n[2]>>m;
  struct us{
    vector<int>par;int val;
    us(int all):par(all),val(0){
      rep(i,0,all-1)par[i]=i;
    }
    int find(int x){
      return par[x]==x?x:par[x]=find(par[x]);
    }
    void unite(int x,int y,bool dt=1){
      x=find(x),y=find(y);
      if(x!=y)par[x]=y,val+=dt;
    }
  };
  struct edges{
    int u,v,c;
  };
  vector<edges>E(m);
  for(auto&[u,v,c]:E){
    char ch;
    cin>>u>>v>>ch,u--,v--,c="rgb"s.find(ch);
  }
  int all=n[0]+n[1]+n[2]+1;
  us cur(all);
  vector U(2,vector(3,us(all)));
  for(auto[u,v,c]:E){
    U[0][c].unite(u,v);
    rep(i,0,2)if(c!=i)U[1][i].unite(u,v);
  }
  string ans;
  for(auto[u,v,c]:E){
    if(cur.find(u)==cur.find(v)){
      ans+="0";continue;
    }
    n[c]--;
    bool can=1;
    rep(i,0,1)rep(j,0,2){
      auto&S=U[i][j];
      S.val-=S.find(u)==S.find(v);
      if(i==0){
        can&=n[j]<=S.val;
      }else{
        can&=n[0]+n[1]+n[2]-S.val<=n[j];
      }
    }
    if(can){
      ans+="1";
      cur.unite(u,v);
      rep(i,0,1)rep(j,0,2){
        auto&S=U[i][j];
        S.unite(u,v,0);
      }
    }else{
      ans+="0";
      n[c]++;
      rep(i,0,1)rep(j,0,2){
        auto&S=U[i][j];
        S.val+=S.find(u)==S.find(v);
      }
    }
  }
  if(ans.find('1')==-1u){
    cout<<"No"<<endl;
  }else{
    cout<<"Yes"<<endl<<ans<<endl;
  }
  return 0;
}
