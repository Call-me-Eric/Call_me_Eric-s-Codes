#include <iostream>
#include <cstdio>
using namespace std;
struct sss{
	int pre;
	int value;
	int next;
}a[100000+5];
int book[100000+5];
int main(){
	int n, m;
	cin >>n;
	for (int i = 1; i <= n; i++){	//��ʼ�� 
		a[i].pre = i; a[i].value = i; a[i].next = i;
	}
	int head = 1, x, y;
	for (int i = 2; i <= n; i++){	//����������� 
		cin >> x >> y;
		if (y == 0){	//����߲������� 
			a[i].next = x;		 	// i���ұ�ָ��x 
			a[i].pre = a[x].pre; 	// i�����ָ��ԭ��x����� 
			a[a[x].pre].next = i;	// ԭ��x����ߵ��ұߵģ���Ϊָ��i
			a[x].pre = i;			//x����߸�Ϊi ///**ע��˳�� ***/// 
			if(x == head)			//���ԭ��x����ͷָ�룬��ͷָ��ָ��i 
				head = i;
			 
		}
		else{			//���ұ߲������ 
			a[i].pre = x;				
			a[i].next = a[x].next;
			a[a[x].next].pre = i;	//ע��˳�� 
			a[x].next = i;			//ע��˳�� 
		}
	}
	cin >>m;	
	// ����ɾ��Ԫ�ز��� 
	for(int i = 1; i <= m; i++){
		int x; cin >> x; book[x] = i;
	}
	int w = n, flag = 0;	 
	while(w--){
		if(book[head]){	//�����ǰ���Ѿ����ɾ���ˣ��ͽ�����һ�� 
			head = a[head].next;
			continue;
		}
		if(flag == 0){
			cout << head;
			flag = 1;
		}
		else{
			cout <<' '<< head<;
		}
	head = a[head].next; 
	}	
	return 0;
}

