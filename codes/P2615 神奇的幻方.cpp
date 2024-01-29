#include <cstdio>
#include <iostream>
using namespace std;
int a[40][40];
int main() {
	int n, i, j, k = 1, cnt ;
	cin >> n;
	i = 1; j = n / 2 + 1; cnt = n*n - 1;
	a[i][j] = k;
	while(cnt--){
		if(i == 1 && j != n){
			i = n;
			j ++;
		}
		else if(j == n && i != 1){
			j = 1;
			i--;
		}
		else if(i == 1 && j == n){
			i++;
		}
		else {
			if(a[i-1][j+1] == 0){
				i--;
				j++;
			}
			else{
				i++;
			}
		}
		a[i][j] = ++k;	
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout << a[i][j] <<' '; 
		}
		cout << endl;
	}
	return 0;
}

