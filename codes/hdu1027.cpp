#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1001];
int n, m; 
int main(){
	while(cin >> n >> m){
		for(int i = 1;i <= n;i++){
			a[i] = i;
		}
		int t = 1;
		do{
			if(t == m)break;
			t++;
		}while(next_permutation(a + 1, a + 1 + n));
		for(int i = 1;i < n;i++){
			printf("%d ",a[i]);
		}
		printf("%d\n",a[n]);
	}
	return 0;
}

