#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,MN=1e5;
int he[N],zhi[N],wei[10],f[N];
void init(){
	for(int i=2;i<=MN;i++){
		if(!he[i])zhi[++zhi[0]]=i;
		for(int j=1;i*zhi[j]<=MN&&j<=zhi[0];j++){
			he[i*zhi[j]]=1;
			if(!(i%zhi[j]))break;
		}
	}
	for(int i=1;i<=MN;i++){
		int m=i,w=0,res=0;
		while(m)wei[++w]=m%10,m/=10;
		for(int l=w;l;l--)
			for(int r=l,sum=0;r;r--)
				sum=sum*10+wei[r],res|=(!he[i]);
		f[i]=f[i-1]+(!res);
	}
}
void work(){int l,r;cin>>l>>r,cout<<f[r]-f[l-1]<<'\n';}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init();
	int _;cin>>_;
	while(_--)work();
	return 0;
}
