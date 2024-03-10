#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define ll long long
using namespace std;
int n, k;
const int maxn = 1e6 * 5 + 10;
int w[maxn],leftt[maxn],rightt[maxn];
bool book[maxn];
struct node{
	int idx,w;
}tmp;
bool operator < (node a,node b){
	return a.w < b.w;
}
priority_queue<node> que;
signed main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++){
		scanf("%d",&w[i]);
		tmp.idx = i;
		tmp.w = w[i];
		leftt[i] = i - 1;
		rightt[i] = i + 1;
		que.push(tmp); 
	}
	//考虑贪心求解，即每次取最大值，并冻结左右树 
	leftt[n + 1] = n;
	rightt[0] = 1;
	long long ans = 0;
	for(int i = 1;i <= k;i++){
		while(!que.empty() && book[que.top().idx])que.pop();
		tmp = que.top();que.pop();
		if(tmp.w < 0)break;
		ans += tmp.w;
		book[leftt[tmp.idx]] = book[rightt[tmp.idx]] = 1;
		tmp.w = w[leftt[tmp.idx]] + w[rightt[tmp.idx]] - w[tmp.idx];
		w[tmp.idx] = tmp.w;//由于取点时可能只是局部最优解，而全局最优解可能取得是当前点的左右，因此提供反悔机制
		//如果取了一个点j,则将w[left[j]] + w[right[j]] - w[j]加入到队列中，如果取了新加入的点，就相当于删除了j
		//并取left[j],right[j]，间接的解决了问题
		leftt[tmp.idx] = leftt[leftt[tmp.idx]];
		rightt[tmp.idx] = rightt[rightt[tmp.idx]];
		rightt[leftt[tmp.idx]] = tmp.idx;
		leftt[rightt[tmp.idx]] = tmp.idx;
		que.push(tmp);
	}
	printf("%lld\n",ans);
	return 0;
}
 
