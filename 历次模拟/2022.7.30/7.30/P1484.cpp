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
	//����̰����⣬��ÿ��ȡ���ֵ�������������� 
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
		w[tmp.idx] = tmp.w;//����ȡ��ʱ����ֻ�Ǿֲ����Ž⣬��ȫ�����Ž����ȡ���ǵ�ǰ������ң�����ṩ���ڻ���
		//���ȡ��һ����j,��w[left[j]] + w[right[j]] - w[j]���뵽�����У����ȡ���¼���ĵ㣬���൱��ɾ����j
		//��ȡleft[j],right[j]����ӵĽ��������
		leftt[tmp.idx] = leftt[leftt[tmp.idx]];
		rightt[tmp.idx] = rightt[rightt[tmp.idx]];
		rightt[leftt[tmp.idx]] = tmp.idx;
		leftt[rightt[tmp.idx]] = tmp.idx;
		que.push(tmp);
	}
	printf("%lld\n",ans);
	return 0;
}
 
