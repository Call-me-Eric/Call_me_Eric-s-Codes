#include<bits/stdc++.h>
int n,k,p[100010],cnt,res,t;
bool v[1000010];
void get(int num){
	for(int i=2;i<=num;i++){
		if(!v[i]){
			p[++cnt]=i;
			for(int j=1;j<=num;j++){
				if(i*j>num) break;
				v[i*j]=1;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&k);
	if(n<=k){
		for(int i=1;i<=n;i++) printf("1");
		return 0;
	}
	get(n);
	for(int i=1;i<=cnt;i++){
		if(n%p[i]==0){
			int ans=k/p[i]*p[i];
			if(ans>res) res=ans,t=p[i];
		}
	}
	if(res==0){
		for(int i=1;i<=n;i++) printf("0");
		return 0;
	}
	for(int i=1;i<=t;i++){
		for(int j=1;j<=res/t;j++) printf("1");
		for(int j=res/t+1;j<=n/t;j++) printf("0");
	}
	return 0;
}
