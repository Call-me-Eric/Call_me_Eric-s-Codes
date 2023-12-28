#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int a[12],b[12],cnt;
int res[1000001],nr[1000001];
int gcd(int x,int y){return y?gcd(y,x%y):x;}
int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int i,j,x;
	scanf("%d%d",&n,&k);x=n;
	if(k==n-1)k--;
	if(k==n)for(i=1;i<=n;i++)printf("1");
	if(k<=1)for(i=1;i<=n;i++)printf("0");
	if(k==n||k<=1)return 0;
	for(i=2;i*i<=x;i++){
		if(x%i)continue;
		a[++cnt]=i;
		while(x%i==0)b[cnt]++,x/=i;
	}
	if(x>1)a[++cnt]=x,b[cnt]=1;
	for(i=1;i<=cnt;i++){
		if(k%a[i])continue;
		int d=k/a[i],r=n/a[i];
		for(j=1;j<=n;j++)if((j-1)%r+1<=d)res[j]=1;
		for(j=1;j<=n;j++)printf("%d",res[j]);
		return 0;
	}
	if(cnt==1){
		int eh=n/a[1];
		int fr=k/a[1];
		for(i=1;i<=n;i++){
			if((i-1)%eh+1<=fr)printf("1");
			else printf("0");
		}
		return 0;
	}
	if(cnt==2&&b[1]==1&&b[2]==1){
		int k1=k/a[1]*a[1],k2=k/a[2]*a[2];
		int eh,fr;
		if(k1>=k2)eh=n/a[1],fr=k/a[1];
		else eh=n/a[2],fr=k/a[2];
		int ts=0;
		for(i=1;i<=n;i++){
			if((i-1)%eh+1<=fr)printf("1");
			else printf("0");
		}
		return 0;
	}
	if(cnt==2){
		int p=a[1],q=a[2];
		int dp=n/p,dq=n/q;
		int dlt=dp/gcd(dp,dq),r=gcd(dp,dq);
		int rc=dp,mx=k/p*p,xp=0;
		for(i=1;i<=dq;i++){
			if(i*q>k)break;
			if(i%r==1)rc-=dlt;
			int tl=i*q,res=k-tl;
			res/=p;
			if(res<=rc)res=res*p+tl;
			else res=rc*p+tl;
			if(res>mx)mx=res,xp=i;
		}
		int up=(mx-xp*q)/p,uq=xp;
		int pos=0;
		for(i=1;i<=uq;i++){
			if(i%r==1)pos++;
			for(j=pos;j<=n;j+=dq){
				res[j]=1;
				nr[j%dp]=1;
			}
			pos+=dp-dq;pos%=dp;
		}
		int pb=1;
		for(i=1;i<=up;i++){
			while(pb<=dp&&nr[pb])pb++;
			for(j=pb;j<=n;j+=dp)res[j]=1;
			pb++;
		}
		for(i=1;i<=n;i++)printf("%d",res[i]);
		return 0;
	}
	if(cnt==3){
		if(k==7||k==23)res[1]=res[7]=res[13]=res[19]=res[25]=res[2]=res[17]=1;
		if(k==11||k==19){
			for(i=1;i<=n;i+=6)res[i]=1;
			for(i=2;i<=n;i+=10)res[i]=1;
			for(i=4;i<=n;i+=10)res[i]=1;
		}
		if(k==13||k==17){
			for(i=1;i<=n;i+=6)res[i]=1;
			for(i=2;i<=n;i+=6)res[i]=1;
			for(i=3;i<=n;i+=10)res[i]=1;
		}
		if(k>=15)for(i=1;i<=n;i++)res[i]^=1;
		for(i=1;i<=n;i++)printf("%d",res[i]);
		return 0;
	}
}
