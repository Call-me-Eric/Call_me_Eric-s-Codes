#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n;
long long b[100001], f[100001],d[100001];
int main(){
	scanf("%d",&n);
	long long t = 0;
	d[1] = 1;
	for(int i = 2;i <= n;i++){
		scanf("%lld",&t);
		f[i] = t;
		d[i] = d[f[i]] + 1;
	}
	for(int i = 1;i <= n;i++){
		scanf("%lld",&b[i]);
		if(b[i] == -1)b[i] = 1000000001;
	}
	for(int i = 2;i <= n;i++){
		if(d[i] % 2){
			b[f[i]] = min(b[f[i]],b[i]);
		}
	}
	long long ans = 0;
	for(int i = 1;i <= n;i++){
		if(b[i] == 1000000001)continue;
		ans += b[i] - b[f[i]];
	}
	printf("%lld",ans);
	return 0;
}

