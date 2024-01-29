#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<string>
#define Max(a,b) (a) > (b) ? (a) : (b)
using namespace std;
int n,m;
int book[200010];
int enter[200001];
int head = 1,tail = 1;
int que[2000001];
long long ans[200001];
long long time[200001];
vector<int> G[200001];
void Bfs(int st){
	while(head != tail){
		int t = que[head];
		for(int i = 0,len = G[t].size() ;i < len;i++){
			enter[G[t][i]]--;
			ans[G[t][i]] = Max(ans[G[t][i]],ans[t] + time[G[t][i]]);
			if(enter[G[t][i]] == 0){
				que[tail++] = G[t][i];
				book[G[t][i]] += 1;
			}
		}
		head++;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i = 1;i <= n;i++){
		scanf("%lld",&time[i]);
		ans[i] = time[i];
	}
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		enter[v]++; 
	}
	int t = -1;
	for(int i = 1;i <= n;i++){
		if(enter[i] == 0){
			t = i;
			que[tail++] = i;
		}
	}
	Bfs(t);
	long long res = -99999999;
	for(int i = 1;i <= n;i++){
		res = Max(res,ans[i]);
	}
	printf("%lld",res);
	return 0;
}
