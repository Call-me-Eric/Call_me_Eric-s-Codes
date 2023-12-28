#include<bits/stdc++.h>
#define LL long long
#define SZ(x) ((LL)(x.size()))
using namespace std;
long long read(){
  long long q=0,w=1;
  char ch=getchar();
  while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){q=q*10+(ch-'0');ch=getchar();}
  return q*w;
}
void write(LL x){
  if(x<0){putchar('-');x=(-x);}
  if(x>9)write(x/10);
  putchar('0'+x%10);
}
void writeln(LL x){write(x);puts("");}
void writecs(LL x){write(x);putchar(' ');}
LL qpow(LL a,LL b,LL p){
  LL ans=1;
  while(b){
    if(b&1)ans=(ans*a)%p;
    b>>=1;a=(a*a)%p;
  }
  return ans;
}
const long long mod = 998244353;
void addmod(LL &x,LL y){x+=y;if(x>=mod)x-=mod;}
void submod(LL &x,LL y){x-=y;if(x<0)x+=mod;}
LL domod(LL x){
  if(x<0)x+=mod;
  if(x>=mod)x-=mod;
  return x;
}
LL inv(LL x){return qpow(x,mod-2,mod);}
const long long N = 100+95 , SIZE = 1000000+95;
long long n,m,a[N],b[N],T,k;vector<LL>A,B;
map<vector<LL>,LL>Id;LL Idx;vector<LL>E[SIZE];LL f[SIZE],g[SIZE];
bool check(vector<LL>now){
  for(LL i=0;i<SZ(now);i++){
    if(now[i]<0)return false;
    if(i>0&&now[i-1]<now[i])return false;
  }
  return true;
}
LL dfs(vector<LL>now,LL dep){
  while(SZ(now)&&!now.back())now.pop_back();
  if(!check(now))return 0;
  if(Id.find(now)!=Id.end())return Id[now];
  LL idx=++Idx;Id[now]=Idx;
  /*  cout<<" idx = "<<idx<<" now : ";
  for(LL i=0;i<SZ(now);i++)
    cout<<now[i]<<" ";
  cout<<endl;*/
  if(!dep)return idx;
  now.push_back(0);LL tmp=0;
  for(LL i=0;i<SZ(now);i++){
    now[i]++;
    tmp=dfs(now,dep-1);
    if(tmp)E[idx].push_back(tmp);
    now[i]--;
    now[i]--;
    tmp=dfs(now,dep-1);
    if(tmp)E[idx].push_back(tmp);
    now[i]++;
  }
  sort(E[idx].begin(),E[idx].end(),[&](LL x,LL y){return x<y;});
  E[idx].erase(unique(E[idx].begin(),E[idx].end()),E[idx].end());
  return idx;
}
int main(){
  freopen("young.in","r",stdin);
  freopen("young.out","w",stdout);
  n=read();
  for(LL i=1;i<=n;i++){a[i]=read();A.push_back(a[i]);}
  m=read();
  for(LL i=1;i<=m;i++){b[i]=read();B.push_back(b[i]);}
  T=read();
  while(T--){
    LL k=read();dfs(A,k);
    if(Id.find(B)==Id.end()){puts("0");continue;}
    for(LL i=0;i<=Idx;i++)f[i]=0;
    f[Id[A]]=1;
    for(LL t=1;t<=k;t++){
      for(LL x=1;x<=Idx;x++){g[x]=f[x];f[x]=0;}
      for(LL x=1;x<=Idx;x++)
	for(LL i=0;i<SZ(E[x]);i++)
	  addmod(f[E[x][i]],g[x]);
    }
    LL ans=f[Id[B]];
    writeln(ans);
  }
  return 0;
}
