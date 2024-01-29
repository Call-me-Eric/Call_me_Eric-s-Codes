#include<bits/stdc++.h>
using namespace std;
int n,k,p[1500005],tt=0;
void jiaS(){p[tt+1]=p[tt]+k;++tt;}
void jiaB(){p[tt+1]=p[tt]+k+1;++tt;}
void jiaSn(){p[tt+1]=p[tt]-k;++tt;}
int main(){
	freopen("didi.in","r",stdin);
	freopen("didi.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(k==1)for(int i=1;i<=n;++i)p[i]=i;
	else{
		p[++tt]=1;
		int f1=2*k+1,f2=(k-1)*f1+1,A=0,B=0;
		for(int i=0;i<=(n-1)/f1;++i)if((n-1-i*f1)%f2==0)A=i,B=(n-1-i*f1)/f2;
		for(int i=1;i<=A;++i){for(int j=1;j<=k;++j)jiaB(),jiaSn();jiaB();}
		for(int i=1;i<=B;++i,jiaS()){
			for(int j=1;j<k;++j){
				jiaS(),jiaB();for(int l=1;l<j;++l)jiaSn(),jiaB();
				jiaSn();for(int l=j;l<k;++l)jiaSn(),jiaB();
			}
		}
	}
	for(int i=1;i<=n;++i)printf("%d",p[i]),putchar(i==n?'\n':' ');
	return 0;
}