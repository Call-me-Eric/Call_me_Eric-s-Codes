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
	for (int i = 1; i <= n; i++){	//初始化 
		a[i].pre = i; a[i].value = i; a[i].next = i;
	}
	int head = 1, x, y;
	for (int i = 2; i <= n; i++){	//处理插入链表 
		cin >> x >> y;
		if (y == 0){	//往左边插入的情况 
			a[i].next = x;		 	// i的右边指向x 
			a[i].pre = a[x].pre; 	// i的左边指向原来x的左边 
			a[a[x].pre].next = i;	// 原来x的左边的右边的，改为指向i
			a[x].pre = i;			//x的左边改为i ///**注意顺序 ***/// 
			if(x == head)			//如果原来x就是头指针，把头指针指向i 
				head = i;
			 
		}
		else{			//往右边插入情况 
			a[i].pre = x;				
			a[i].next = a[x].next;
			a[a[x].next].pre = i;	//注意顺序 
			a[x].next = i;			//注意顺序 
		}
	}
	cin >>m;	
	// 处理删除元素部分 
	for(int i = 1; i <= m; i++){
		int x; cin >> x; book[x] = i;
	}
	int w = n, flag = 0;	 
	while(w--){
		if(book[head]){	//如果当前的已经标记删除了，就进行下一个 
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

