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
const string pr[100] = {"11","19","41","61","89","409","449","499","881","991","6469","6949","9001","9049","9649","9949","60649","666649","946669","60000049","66000049","66600049"};
const char tr[10] = {'0','1','4','6','8','9'};const long long LIM = 22;LL LEN[100];
const long long N = 100000+95 , SIZE = 500000+95;
map<vector<LL>,LL>Id;LL Idx;vector<LL>E[SIZE];
LL dfs(vector<LL>now){
  for(LL i=0;i<SZ(now);i++)
    if(now[i]>=LEN[i])return 0;
  if(Id.find(now)!=Id.end())return Id[now];
  LL idx=++Idx;Id[now]=Idx;
  for(LL t=0;t<=5;t++){
    vector<LL>nxt=now;
    for(LL i=0;i<SZ(nxt);i++)
      if(pr[i][nxt[i]]==tr[t])nxt[i]++;
    E[idx].push_back(dfs(nxt));
  }
  return idx;
}
#define mp(a,b) make_pair(a,b)
#define fir first
#define sec second
LL s,f[SIZE][2],g[SIZE][2];
inline LL calc(string lim){
  for(LL x=0;x<=Idx;x++)
    for(LL op=0;op<=1;op++)f[x][op]=0;
  LL len=SZ(lim);f[s][1]=1;
  for(LL t=0;t<len;t++){
    for(LL x=1;x<=Idx;x++)
      for(LL op=0;op<=1;op++){g[x][op]=f[x][op];f[x][op]=0;}
    for(LL x=1;x<=Idx;x++)
      for(LL i=0;i<=5;i++){
	for(LL op=0;op<=1;op++)
	  if(E[x][i]){
	    if(op&&lim[t]<tr[i])continue;
	    addmod(f[E[x][i]][op&(lim[t]==tr[i])],g[x][op]);
	  }
      }
  }
  LL ans=0;
  for(LL x=1;x<=Idx;x++)
    for(LL op=0;op<=1;op++)addmod(ans,f[x][op]);
  return ans;
}
int main(){
  freopen("prime.in","r",stdin);
  freopen("prime.out","w",stdout);
  for(LL i=0;i<LIM;i++)LEN[i]=SZ(pr[i]);
  vector<LL>now;
  for(LL i=0;i<LIM;i++)now.push_back(0);
  s=dfs(now);
  //  cout<<" Idx = "<<Idx<<endl;
  /*  for(auto x:Id){
    for(LL i=0;i<SZ(x.fir);i++)
      cout<<x.fir[i]<<" ";
    cout<<" -> x.sec = "<<x.sec<<endl;
  }*/
  LL T=read();
  while(T--){
    LL l=read(),r=read();
    writeln(domod(calc(to_string(r))-calc(to_string(l-1))));
  }
  return 0;
}
