//注：此题为二分答案法 
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, k, a[100010];
int l, r, mid, ans;
int t = -9999999;
bool fun(int t){
	int sum = 0;
	for(int i = 1;i <= n;i++){
		sum += a[i] / t;
	}
	return sum >= k;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		t = max(a[i], t);
	}
	l = 1;r = t + 1;
	while(l <= r){
		mid = l + (r - l) / 2;
		if(fun(mid)){
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	printf("%d",ans);
	return 0;
}
