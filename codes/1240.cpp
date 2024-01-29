#include <cstdio>
#include <cmath>
using namespace std;
int a[1000001];
int ans;
/*void find(int left, int right, int key){
	if(left > right)return;
	int mid = (left + right) / 2, cha;
	if(key == a[mid]){ans = a[mid];return;}
	else if(key < a[mid]){cha = a[mid] - key;find(left, mid, key);}
	else {ans = a[mid];cha = key - a[mid];find(mid + 1, right, key);}
	if(cha < abs(ans - key)){
		if(a[mid] <= ans)
			ans = a[mid];
	}
	return;
}*/
int main() {
	int n, m, key;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)	scanf("%d",&a[i]);
	scanf("%d",&m);
	while(m--){
	scanf("%d",&key);
	int k = abs(a[1] - key),ans = a[1];
	 for(int i = 2;i <= n;i++){
		if(abs(a[i] - key) < k){
			k = abs(a[i] - key);ans = a[i];
		}
	}
	printf("%d\n",ans);}
	return 0;
}

