#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
long long a[41],total,ans = 9999999999;
int n;
void dfs(int pos,long long sum){
	if(pos > n){
		return;
	}
	if(2 * sum > total + ans){
		return;
	}
		int tmp = llabs(sum  - (total - sum));
		if(ans > tmp)ans = tmp;
	dfs(pos + 1,sum);
	dfs(pos + 1,sum + a[pos]);
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
		total += a[i];
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}

