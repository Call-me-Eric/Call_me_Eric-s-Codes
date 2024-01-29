//注：此代码为二分答案法 
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int INF = 1e9;
int n, x[1000001], c;
int L, R, mid, ans;
bool fun(int t){
	int k = 0, last = -INF;
	for(int i = 1;i <= n;i++){
		if(x[i] - last >= t){
			k++;last = x[i];
		}
	}
	return k >= c;
}
int main(){
	scanf("%d%d",&n,&c);
	for(int i = 1;i <= n;i++){
		scanf("%d",&x[i]);
	}
	L = 1;R = INF;
	sort(x + 1,x + 1 + n);
	while(L <= R){
		mid = L + (R - L) / 2;
		if(fun(mid)){
			ans = mid;
			L = mid + 1;
		}
		else {
			R = mid - 1;
		}
	}
	printf("%d",ans);
	return 0;
}
