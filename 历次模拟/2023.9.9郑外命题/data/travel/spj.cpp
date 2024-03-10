#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
typedef long long ll;
vector<int> G[N];
int p[N],fa[N],deep[N];
int dfs(int now,int f=0){
  deep[now]=deep[f]+1;
  fa[now]=f;
  for(int i=0;i<G[now].size();i++){
    int to=G[now][i];
    if(to==f) continue;
    dfs(to,now);
  }
}
bool dis(int x,int y,int k){
  while(k--){
    if(deep[x]>=deep[y]){
      x=fa[x];
    }else{
      y=fa[y];
    }
    if(x==y) return true;
  }
  return false;
}
int main(int argc, char *argv[]) {
  int score = atoi(argv[4]);            // full score of this test case
  std::ifstream fin(argv[1]);         // where to read the input
  std::ifstream fstd(argv[3]);          // where to read the jury's answer
  std::ifstream fout(argv[2]);       // where to read the participant's output
  std::ofstream fscore(argv[5]);    // where to write the score
  std::ofstream freport(argv[6]);  // where to write the feedback information
  int n,k;
  fin>>n>>k;
  for(int i=1;i<n;i++){
    int u,v;fin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for(int i=1;i<=n;i++){
    fin>>p[i];
  }
  ll ans,out;
  fstd>>ans;
  fout>>out;
  if(ans!=out){
    fscore<<0<<endl;
    return 0;
  }
  int bs;
  fout>>bs;
  if(bs>n||bs<1){
    fscore<<0<<endl;
    return 0;
  }
  vector<int> lj;set<int> st;
  for(int i=0;i<bs;i++){
    int tmp;fout>>tmp;
    lj.push_back(tmp);
    st.insert(tmp);
  }
  if(lj.size()!=st.size()||lj.size()==0||lj[0]!=1){
    fscore<<0<<endl;
    return 0;
  }
  ll sum=0;
  for(int i=0;i<lj.size();i++){
    sum+=p[lj[i]];
  }
  if(sum!=ans){
    fscore<<0<<endl;
    return 0;
  }
  dfs(1);
  for(int i=1;i<lj.size();i++){
    if(dis(lj[i-1],lj[i],k)==false){
      fscore<<0<<endl;
      return 0;
    }
  }
  fscore<<score<<endl;
  return 0;
}