#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
int n,k;
set<int> ans;
void dfs(int last,int num,int pos){
	if(n == pos){
		ans.insert(num);
		return; 
	}
	if(last - k >= 0){
		dfs(last - k,num * 10 + last - k, pos + 1);
	}
	
	if(last + k < 10){
		dfs(last + k,num * 10 + last + k, pos + 1);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= 9;i++){
		dfs(i,i,1);
	}
	set<int>::iterator it = ans.begin();
	for(;it != ans.end();it++){
		printf("%d ",*it);
	}
	return 0;
}

