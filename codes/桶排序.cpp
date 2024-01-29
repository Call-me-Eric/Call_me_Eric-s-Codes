#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1000001;
int a[N/*数据的最大值加一*/];
int main() {
	int t, n;
	int i;
	scanf("%d",&n);
	for(i = 1;i <= n;i++){//桶排序输入 
		scanf("%d",&t);
		a[t]++;//关键！将第t号桶标记 
	}
	int first = 1, j;
	for(i = 1;i <= N;i += 2){//忽视偶数的存在 
		for(j = 1;j <= a[i];j++){//输出多少次。。。 
			if(first){//关于逗号的问题。。。 
				printf("%d",i);
				first = 0; 
			}
			else{
				printf(",%d",i);
			}//不必我说了吧？ 
		}
	}
	return 0;
}

