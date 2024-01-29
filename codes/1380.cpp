#include <cstdio>
using namespace std;
int a[1001], n;
int main() {
	int ave = 0, ans = 0, sum = 0; 
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		sum += a[i];
	}
	ave = sum / n;
	for(int i = 1;i <= n;i++)a[i] -= ave;
	for(int i = 1;i < n;i++){
		if(a[i] == 0) continue;
		ans++;a[i + 1] += a[i];
	}
	printf("%d",ans);
	return 0;
}

