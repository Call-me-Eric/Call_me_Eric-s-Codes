#include<bits/stdc++.h>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
int n,k,Ans[1000005];vector<int>fac;
bool isprime(int x){
	for(int i=2;i*i<=x;i++)
		if(x%i==0)return false;
	return true;
}
signed main(){
	file("ur");
	n=read();k=read();
	if(k==n){while(n--)putchar('1');return 0;}
	if(k<=1){while(n--)putchar('0');return 0;}
	int r=n;
	for(int i=2;i*i<=r;i++)
		if(r%i==0){
			fac.emplace_back(i);
			while(r%i==0)r/=i;
		}
	if(r>1)fac.emplace_back(r);
	if(fac.size()==0){while(n--)putchar('0');return 0;}
	if(n<=20){
		int ans=0,sta=0;
		for(int s=0;s<1<<n;s++){
			int ppcnt=__builtin_popcount(s);
			if(ppcnt>k)continue;
			bool flag=false;
			for(auto u:fac){
				bool flg=true;
				for(int i=0;i<n;i++)
					flg&=(((s>>i)&1)==((s>>((i+(n/u))%n))&1));
				flag|=flg;
			}
			if(flag&&ppcnt>ans)ans=ppcnt,sta=s;
		}
		for(int i=0;i<n;i++)printf("%d",(sta>>i)&1);
		return 0;
	}
	if((fac.size()==2&&fac[0]*fac[1]==n)||(fac.size()==1&&fac[0]*fac[0]==n)){
		if(fac.size()==1)fac.emplace_back(fac[0]);
		int ans1=k/fac[0]*fac[0],ans2=k/fac[1]*fac[1];
		int chos=ans1>ans2?1:0,cnt=k/fac[chos^1];
		for(int i=0;i<n;i++)
			if(cnt){
				for(int j=i;!Ans[j];j=(j+fac[chos])%n)Ans[j]=1;
				cnt--;
			}
		for(int i=0;i<n;i++)printf("%d",Ans[i]);
	}
	return 0;
}
