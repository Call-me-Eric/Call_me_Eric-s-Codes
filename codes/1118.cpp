#include <iostream>
#include <cstdio>
using namespace std;
int a[100001], b[100001], x[100001], y[100001];
int main() {
	int n, tx, ty;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d%d%d",&a[i],&b[i],&x[i],&y[i]);
	}
	scanf("%d%d",&tx,&ty);
	for(int i = n;i >= 1;i--){
		if(a[i] <= tx && a[i] + x[i] >= tx && b[i] <= ty && b[i] + y[i] >= ty){
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}

