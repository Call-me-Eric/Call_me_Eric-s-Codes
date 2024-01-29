#include<cstdio>
using namespace std;
int n, m, l;
int a[100010], ans;
int left, right, mid;
bool fun(int t){
	int k = 0, last = 0;
	for(int i = 1;i <= n;i++){
		if(a[i] - last < t){
			k++;
		}
		else last = a[i];
	}
	return k <= m;
}
int main(){
	scanf("%d%d%d",&l,&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	left = 1;right = l;
	while(left <= right){
		mid = left + (right - left) / 2;
		if(fun(mid)){
			ans = mid;
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	printf("%d",ans);
	return 0;
}
