#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll ran(ll l,ll r){
	return rng()%(r-l+1)+l;
}
int n,pr[10000010],p=0,b[100];
bool isnt[10000010];
void init(int N){
	for(int i=2;i<=N;i++){
		if(!isnt[i]){
			pr[++p]=i;
//			cerr<<i<<"\n"; 
		}
		for(int j=1;j<=p&&pr[j]*i<=N;j++){
			isnt[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
}
int main(){
	int lim=1e9;
	init(min(lim,10000000));
	n=ran(14,20);
	for(int i=1;i<=p;i++) if(1ll*pr[i]*pr[i]>lim){
		b[0]=i;
		for(int j=1;j<100;j++) b[j]=ran(i+1,p);
		break;
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		int w;
		if(rng()&1) w=pr[b[ran(0,4)]];
		else w=1;
		while(w<=lim){
			int v=ran(1,b[0]-1);
			if(1ll*w*pr[v]<=lim) w*=pr[v];
			else if(rng()&1) break;
		}
		printf("%d ",w);
	}
	puts("");
}

