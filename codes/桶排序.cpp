#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1000001;
int a[N/*���ݵ����ֵ��һ*/];
int main() {
	int t, n;
	int i;
	scanf("%d",&n);
	for(i = 1;i <= n;i++){//Ͱ�������� 
		scanf("%d",&t);
		a[t]++;//�ؼ�������t��Ͱ��� 
	}
	int first = 1, j;
	for(i = 1;i <= N;i += 2){//����ż���Ĵ��� 
		for(j = 1;j <= a[i];j++){//������ٴΡ����� 
			if(first){//���ڶ��ŵ����⡣���� 
				printf("%d",i);
				first = 0; 
			}
			else{
				printf(",%d",i);
			}//������˵�˰ɣ� 
		}
	}
	return 0;
}

