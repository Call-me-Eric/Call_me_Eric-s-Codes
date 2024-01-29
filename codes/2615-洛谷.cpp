#include <cstdio>
#include <iostream>
using namespace std;
int a[40][40];
int n;
int x, y, k;
int main() {
	scanf("%d",&n);
	a[x = 1][y = (n / 2 + 1)] = k = 1;
	k++;
	while(k <= n * n){
		if(x == 1 && y != n){y += 1;	x = n;}
		else 
		if(x != 1 && y == n){x -= 1;	y = 1;}
		else
		if(x == 1 && y == n){x += 1;}
		else
		if(a[x - 1][y + 1] == 0){x -= 1;	y += 1;}
		else {x += 1;}
		a[x][y] = k;
		k++;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			printf("%d ",a[i][j]);
		}
		putchar(10);
	}
	return 0;
}

