#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int col[100001]; 
vector<int> G[100001];
int n, m;
bool dfs(int root,bool flag){
	col[root] = flag;
	int t = 0;
	for(int i = 0,len = G[root].size();i < len;i++){
		t = G[root][i];
		if(col[t] == col[root])return false;
		else if(col[t] == -1)return dfs(t,!flag);
	}
	return true;
}
int main(){
	int t1,t2;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&t1,&t2);
		G[t1].push_back(t2);
		G[t2].push_back(t1);  
	}
	memset(col,-1,sizeof(col)); 
	for(int i = 1;i <= n;i++){
		if(col[i] == -1)if(dfs(i,0) == false)printf("false at %d\n",i);
	}
	return 0;
}

