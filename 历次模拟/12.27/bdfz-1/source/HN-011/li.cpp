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
#define PLL pair<LL,LL>
#define mp(a,b) make_pair(a,b)
#define fir first
#define sec second
const long long N = 200000+95 , M = 200000+95;
long long n,m,deg[N];vector<PLL>E;LL sum[N];vector<LL>vc[N];

LL fa[N],dat[N],cnt[N];
LL find(LL x){return (fa[x]==x?x:(fa[x]=find(fa[x])));}
LL merge(LL x,LL y){//x->y
  x=find(x);y=find(y);
  if(x==y)return 0;
  fa[x]=y;dat[y]+=dat[x];return 1;
}
LL s1(LL l,LL r){return (((l+r)*(r-l+1))>>1);}
int main(){
  freopen("li.in","r",stdin);
  freopen("li.out","w",stdout);
  n=read();m=read();
  for(LL i=1;i<=m;i++){
    LL u=read(),v=read();
    deg[u]++;deg[v]++;
    E.push_back(mp(u,v));
  }
  for(LL i=0;i<SZ(E);i++){
    LL d=(deg[E[i].fir]+deg[E[i].sec]-2);
    if(d>2){puts("-1");return 0;}
  }
  for(LL i=0;i<SZ(E);i++){
    LL u=E[i].fir,v=E[i].sec;
    vc[u].push_back(i+1);
    vc[v].push_back(i+1);
  }
  for(LL i=1;i<=m;i++)fa[i]=i;
  for(LL x=1;x<=n;x++)
    for(LL i=0;i<SZ(vc[x]);i++)
      for(LL j=i+1;j<SZ(vc[x]);j++){
	merge(vc[x][i],vc[x][j]);
	dat[find(vc[x][i])]++;
      }
  for(LL i=1;i<=m;i++)cnt[find(i)]++;
  bool fl=false;
  for(LL i=1;i<=m;i++){
    if(find(i)!=i)continue;
    if(cnt[i]==dat[i]){fl=true;break;}
  }
  if(!fl){
    LL ans=n;
    for(LL i=1;i<=m;i++){
      if(find(i)!=i)continue;
      ans+=s1(1,cnt[i]);
      //      cout<<" i = "<<i<<" cnt[i] = "<<cnt[i]<<endl;
    }
    writecs(0);writeln(ans);
  }
  else {
    LL ans=0;
    for(LL i=1;i<=m;i++){
      if(find(i)!=i)continue;
      if(cnt[i]==dat[i])ans+=cnt[i];
    }
    writecs(1);writeln(ans);
  }
  return 0;
}
