#include <cstdio>
using namespace std;
int a[101];
int main() {
	int temp,i = 1;
	while(1){
		scanf("%d",&temp);
		if(temp == 0) break;
		a[i++] = temp;
	}
	for (int j = i - 1; j > 0; j--)
		printf("%d ",a[j]);
	return 0;
}
