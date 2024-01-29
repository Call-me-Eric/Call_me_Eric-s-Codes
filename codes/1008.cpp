#include <cstdio>
#include <cstring>
using namespace std;
int a[10];
int main() {
	for (int i = 123; i  <= 333; i ++){		//999 / 3 = 333
		memset(a,0,sizeof(a));
		int flag = 1;
		//第一个数的各个位存到数组对应的位数里面加一 
		a[i / 100] ++; 
		a[i /10 % 10] ++;
		a[i % 10] ++ ;
		//第二个
		int j = 2 * i;
		//if(j >987) break;
		a[j / 100] ++; 
		a[j /10 % 10] ++;
		a[j % 10] ++ ;
		//第三个
		int k = 3 * i;
		//if(k >987) break;
		a[k / 100] ++; 
		a[k /10 % 10] ++;
		a[k % 10] ++ ;
		for (int m = 1; m <= 9; m++){
			if(a[m] != 1 ){
				flag = 0;
				break;
			}
		}
		if(flag)
				printf("%d %d %d\n",i,j,k);	
		
	}
	return 0;
}
