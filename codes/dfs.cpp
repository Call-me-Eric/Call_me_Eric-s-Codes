#include<iostream>
#include<cstdio>
using namespace std;
int n, a[1001];
bool book[11];
void dfs(int step){
	if(step > n){
		for(int i = 1;i <= n;i++){
			printf("%5d",a[i]);
		}
		printf("\n");
		return;
	}
	else{
		for(int i = 1;i <= n;i++){
			if(book[i]){
				continue;
			}
			book[i] = true;
			a[step] = i;
			dfs(step + 1);
			book[i] = false;
		}
		return;
	}
}
int main(){
	cin >> n;
	dfs(1);
	return 0;
}
