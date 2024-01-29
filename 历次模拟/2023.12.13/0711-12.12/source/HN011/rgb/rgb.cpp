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
#define popcount(x) (__builtin_popcountll(x))
struct uf{
  vector<LL>fa;
  void init(LL _size){
    fa.resize(_size+2);
    for(LL i=1;i<=_size;i++)fa[i]=i;
  }
  LL find(LL x){return (fa[x]==x?x:(fa[x]=find(fa[x])));}
  LL merge(LL x,LL y){
    x=find(x);y=find(y);
    if(x==y)return 0;
    fa[x]=y;return 1;
  }
};
const long long N = 250+95 , M = 100000+95;
long long n,c[3],m;struct edge{LL u,v,w;}a[M];
LL tr(char c){
  if(c=='r')return 0;
  if(c=='g')return 1;
  return 2;
}
LL fa[N];
LL find(LL x){return (fa[x]==x?x:(fa[x]=find(fa[x])));}
//void merge(LL x,LL y){fa[find(x)]=find(y);}//x->y
LL merge(LL x,LL y){
  x=find(x);y=find(y);
  if(x==y)return 0;
  fa[x]=y;return 1;
}
namespace sub1{
  void solve(){
    for(LL x=0;x<(1<<m);x++){
      if(popcount(x)!=(n-1))continue;
      for(LL i=1;i<=n;i++)fa[i]=i;
      LL _c[3],SUM=0;_c[0]=_c[1]=_c[2]=0;
      for(LL i=0;i<m;i++)
	if((x>>i)&1){SUM+=merge(a[i+1].u,a[i+1].v);_c[a[i+1].w]++;}
      if(SUM!=(n-1))continue;
      bool fl=true;
      for(LL i=0;i<=2;i++)
	if(_c[i]!=c[i]){fl=false;break;}
      if(!fl)continue;
      puts("YES");
      for(LL i=0;i<m;i++)
	cout<<((x>>i)&1);
      cout<<endl;
      return ;
    }
    puts("NO");
    return ;
  }
}
#define PLL pair<LL,LL>
#define mp(a,b) make_pair(a,b)
#define fir first
#define sec second
bool del[M],ans[M];
void make(){
  uf T[3];
  for(LL i=0;i<=2;i++)T[i].init(n);
  for(LL i=1;i<=m;i++){
    LL u=a[i].u,v=a[i].v,w=a[i].w;
    if(!T[w].merge(u,v))del[i]=true;
  }
  return ;
}
namespace sub2{
  uf dat;
  bool check(){
    uf tmp=dat;LL mx=0,mn=0;
    for(LL i=1;i<=m;i++){
      if(del[i])continue;
      LL u=a[i].u,v=a[i].v,w=a[i].w;if(w==2)continue;
      if(w==0)mx+=tmp.merge(u,v);
    }
    tmp=dat;
    for(LL i=1;i<=m;i++){
      if(del[i])continue;
      LL u=a[i].u,v=a[i].v,w=a[i].w;if(w==2)continue;
      if(w==1)tmp.merge(u,v);
    }
    for(LL i=1;i<=m;i++){
      if(del[i])continue;
      LL u=a[i].u,v=a[i].v,w=a[i].w;if(w==2)continue;
      if(w==0)mn+=tmp.merge(u,v);
    }
    //    cout<<" mn = "<<mn<<" c[0] = "<<c[0]<<" mx = "<<mx<<endl;
    return (mn<=c[0]&&c[0]<=mx);
  }
  void solve(){
    dat.init(n);
    for(LL i=1;i<=m;i++){
      if(del[i])continue;
      LL u=a[i].u,v=a[i].v,w=a[i].w;if(w==2)continue;
      if(dat.find(u)==dat.find(v))continue;
      uf tmp=dat;dat.merge(u,v);c[w]--;ans[i]=true;
      if(!check()){dat=tmp;c[w]++;ans[i]=false;}
      //      else cout<<"> i = "<<i<<" a[i].u = "<<a[i].u<<" a[i].v = "<<a[i].v<<" a[i].w = "<<a[i].w<<endl;
    }
    for(LL i=1;i<=n;i++)
      if(dat.find(i)!=dat.find(1)){puts("NO");return ;}
    puts("YES");
    for(LL i=1;i<=m;i++)cout<<ans[i];
    cout<<endl;
    return ;
  }
}
namespace GenHelper{
#define ull unsigned long long
  ull seed=19260817ull;
  void Get(){
    seed^=(seed<<7);
    seed^=(seed>>11);
    seed^=(seed<<13);
    return ;
  }
  ull Rand(){Get();return (seed^(seed<<32ull));}
}using GenHelper::Rand;
#define random(a,b) (Rand()%(b-a+1)+a)
namespace sub3{
  LL ord[M];
  void solve(){
    for(LL i=1;i<=m;i++)ord[i]=i;
    for(LL i=1;i<=m;i++)
      swap(ord[i],ord[random(1,m)]);
    uf dat;dat.init(n);
    for(LL t=1;t<=m;t++){
      LL idx=ord[t];
      //      cout<<" idx = "<<idx<<endl;
      LL u=a[idx].u,v=a[idx].v,w=a[idx].w;
      if(dat.find(u)!=dat.find(v)&&c[w]>0){dat.merge(u,v);c[w]--;ans[idx]=true;}
    }
    for(LL i=1;i<=n;i++)
      if(dat.find(i)!=dat.find(1)){puts("NO");return ;}
    puts("YES");
    for(LL i=1;i<=m;i++)cout<<ans[i];
    cout<<endl;
    return ;
  }
}
namespace sub4{
  LL ord[M];
  void solve(){
    for(LL i=1;i<=m;i++)ord[i]=i;
    for(LL i=1;i<=m;i++)
      swap(ord[i],ord[random(1,m)]);
    do{
      for(LL i=1;i<=m;i++)
	swap(ord[i],ord[random(1,m)]);
      uf dat;dat.init(n);LL _c[3];
      for(LL i=0;i<=2;i++)_c[i]=c[i];
      for(LL t=1;t<=m;t++){
	LL idx=ord[t];
	LL u=a[idx].u,v=a[idx].v,w=a[idx].w;
	if(dat.find(u)!=dat.find(v)&&_c[w]>0){dat.merge(u,v);_c[w]--;ans[idx]=true;}
      }
      if(!_c[0]&&!_c[1]&&!_c[2]){
	puts("YES");
	for(LL i=1;i<=m;i++)cout<<ans[i];
	cout<<endl;return ;
      }
      for(LL i=1;i<=m;i++)ans[i]=0;
    }while(clock()*1.0/CLOCKS_PER_SEC<1.9);
    puts("NO");
    return ;
  }
}
int main(){
  freopen("rgb.in","r",stdin);
  freopen("rgb.out","w",stdout);
  for(LL op=0;op<=2;op++){c[op]=read();n+=c[op];}
  n++;m=read();
  for(LL i=1;i<=m;i++){
    LL u=read(),v=read();char c;cin>>c;
    a[i]=(edge){u,v,tr(c)};
  }
  if(n<=5){
    sub1::solve();
    return 0;
  }
  make();
  if(c[2]==0){
    sub2::solve();
    return 0;
  }
  if(m==((n*(n-1))>>1)&&c[0]==((n-1)/3)&&c[1]==((n-1)/3)&&c[2]==((n-1)/3)){
    sub3::solve();
    return 0;
  }
  sub4::solve();
  return 0;
}
