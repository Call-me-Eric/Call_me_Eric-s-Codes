#include <bits/stdc++.h>
using namespace std;
map<int,long long>sum;
int main(){
	int n;
	cin>>n;
	for(int i=1,tp,w;i<=n;i++){
		cin>>w,tp=w;
		for(int i=2;i*i<=tp;i++) if(tp%i==0){
			while(tp%i==0) tp/=i;
			sum[i]+=w;
		}
		if(tp>1) sum[tp]+=w;
	}
	long long ans=0;
	for(auto i:sum) ans=max(ans,i.second);
	printf("%lld\n",ans);
} 
