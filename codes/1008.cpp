#include <cstdio>
#include <cstring>
using namespace std;
int a[10];
int main() {
	for (int i = 123; i  <= 333; i ++){		//999 / 3 = 333
		memset(a,0,sizeof(a));
		int flag = 1;
		//��һ�����ĸ���λ�浽�����Ӧ��λ�������һ 
		a[i / 100] ++; 
		a[i /10 % 10] ++;
		a[i % 10] ++ ;
		//�ڶ���
		int j = 2 * i;
		//if(j >987) break;
		a[j / 100] ++; 
		a[j /10 % 10] ++;
		a[j % 10] ++ ;
		//������
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
