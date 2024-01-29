#include <iostream>
#include <cstdio>
#define inf 99999999

using namespace std;

int n, ans;

int dfs(int);

int dfs(int step){ 
	if(step == 1)return 0;
	else return dfs(step - 1) + ++ans;
} 

int main(){
	scanf("%d",&n);
	
	printf("%d",dfs(n + 1));
	return 0;
}

