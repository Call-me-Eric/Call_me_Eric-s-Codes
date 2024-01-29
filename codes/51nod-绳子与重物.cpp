#include<iostream>
#include<cstdio>
using namespace std;
int n, ans;
long long c[50001], w[50001], p[50001],f[50001];
int getf(int x){
	int i = x;
	i = p[i];
	while(i != -1){
		w[i] += w[x];
		if(c[i] < w[i]){
			return 1;
		}
		i = p[i];
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(ans = 0;ans < n;ans++){
		scanf("%lld%lld%lld",&c[ans],&w[ans],&p[ans]);
		if(c[ans] < w[ans] || getf(ans))break;
	}
	printf("%d",ans);
	return 0;
}

