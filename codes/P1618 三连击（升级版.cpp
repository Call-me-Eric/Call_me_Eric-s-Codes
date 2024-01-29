#include <iostream>
#include <cstdio>
using namespace std;
int n[10] = {0,1,2,3,4,5,6,7,8,9}, l[10];
int num = 0;
void dfs(int x,int step){
	if(step == 4){
	}
	for(int i = 1; i <= 9; i++){
		if(l[i] == 0) {
			num = num*10 + n[i];
			dfs(x,step+1);
		}
	}
	
}
int main(){
	int a,b,c;
	cin >> a >> b >> c;
	dfs(1,1);
	return 0;
}

