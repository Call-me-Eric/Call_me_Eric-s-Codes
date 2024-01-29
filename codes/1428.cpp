#include <cstdio>
using namespace std;
int a[101],b[101];
int main() {
	int n, num;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%d",&a[i]);
	for (int j = 1; j <= n; j++){
		num = 0;
		for(int k = 1; k <= j - 1; k++){
			if(a[j] > a[k])
				num++;
		}
		b[j] = num;
	}
	for (int i = 1; i <= n; i++)
		printf("%d ",b[i]);
	return 0;
}
