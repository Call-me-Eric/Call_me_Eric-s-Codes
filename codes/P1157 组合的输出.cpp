#include <iostream>
#include <cstdio>

using namespace std;
int a[22], book[22],n, m;
void dfs(int box){
	if(box > m){
		for (int i = 1; i <= m; i++)
			printf("%3d", a[i]);
		printf("\n");
		return;
	}
	for (int i = a[box - 1]+ 1; i <= n; i++){	
		if(!book[i]){
			a[box] = i;
			book[i] = 1;
			dfs(box + 1);	
			book[i] = 0;
		}
	}
}
int main(){
	scanf("%d%d", &n, &m);
	dfs(1);
	return 0;
}

