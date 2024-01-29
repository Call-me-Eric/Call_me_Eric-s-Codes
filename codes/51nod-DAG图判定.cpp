#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
using namespace std;
int n,m;
int book[100010];
int enter[100001];
int head = 1,tail = 1;
int que[100001];
vector<int> G[100001];
bool Bfs(int der[],int st){
	que[tail++] = st;
	book[st] = 1;
	while(head != tail){
		int t = que[head];
		for(int i = 0,len = G[t].size() ;i < len;i++){
			der[G[t][i]]--;
			if(der[G[t][i]] == 0){
				que[tail++] = G[t][i];
				book[G[t][i]] += 1;
			}
		}
		head++;
	}
	for(int i = 1;i <= n;i++){
		if(book[i] != 1){
			return false;
		}
	}
	return true;
}
int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		enter[v]++; 
	}
	int t = -1;
	for(int i = 1;i <= n;i++){
		if(enter[i] == 0)t = i;
	}
	printf("%s",Bfs(enter,t) ? "Yes" : "No");
	return 0;
}

