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
const long long N = 700+95;
long long n,q,a[N][N],mat[N][N];
void gauss(){
  for(LL i=1;i<=n;i++)
    for(LL j=1;j<=n+1;j++)mat[i][j]=a[i][j];
  /*  cout<<"> mat : "<<endl;
  for(LL i=1;i<=n;i++){
    for(LL j=1;j<=n+1;j++)cout<<mat[i][j]<<" ";
    cout<<endl;
  }*/
  LL l=1,r=n;
  for(LL t=1;t<=n;t++){
    LL pos=l;
    for(LL i=l;i<=r;i++)
      if(mat[i][t]){pos=i;break;}
    if(!mat[pos][t])continue;
    for(LL i=t;i<=n+1;i++)
      swap(mat[l][i],mat[pos][i]);
    LL k=inv(mat[l][t]);
    for(LL i=t;i<=n+1;i++)mat[l][i]=(mat[l][i]*k)%mod;
    for(LL i=1;i<=n;i++){
      if(i==l)continue;
      LL k=mat[i][t];if(!k)continue;
      for(LL j=t;j<=n+1;j++)
	submod(mat[i][j],k*mat[l][j]%mod);
    }
    l++;
    /*    cout<<"   >---> t = "<<t<<endl;
    for(LL i=1;i<=n;i++){
      for(LL j=1;j<=n+1;j++)cout<<mat[i][j]<<" ";
      cout<<endl;
    }*/
  }
  if(l<=r){
    bool fl=true;
    for(LL i=l;i<=r;i++)
      if(mat[i][n+1]){fl=false;break;}
    if(fl)puts("Many");
    else puts("No");
    return ;
  }
  for(LL i=1;i<=n;i++)
    writecs(mat[i][n+1]);
  puts("");
  return ;
}
int main(){
  freopen("eq.in","r",stdin);
  freopen("eq.out","w",stdout);
  n=read();q=read();
  for(LL i=1;i<=n;i++)
    for(LL j=1;j<=n+1;j++)a[i][j]=read();
  //  if(q<=2||n<=100){
    gauss();
    while(q--){
      LL z=read();
      for(LL i=1;i<=n+1;i++)a[z][i]=read();
      gauss();
    }
    return 0;
    //  }
  
  return 0;
}
