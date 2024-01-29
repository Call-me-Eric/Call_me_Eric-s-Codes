#include <cmath>
#include <cstdio>
using namespace std;
int main(){
	int n;int sum = 0;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		int t = (int)sqrt(i);
		if(t * t == i)sum++;
	}
	printf("%d",sum);
	return 0;
}


