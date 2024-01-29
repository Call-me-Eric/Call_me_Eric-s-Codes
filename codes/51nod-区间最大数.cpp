#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int M = 200010;
int lt[M << 5], rt[M << 5], sum[M << 5], version[M];
int a[M], b[M];
int n, size_tree;
int m, point;
void build(int &u,int l,int r){
	u = ++size_tree;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(lt[u], l, mid);
	build(rt[u], mid + 1, r);
}
int modify(int history,int l,int r){
	int now = ++size_tree;
	lt[now] = lt[history];
	rt[now] = rt[history];
	sum[now] = sum[history] + 1;//如果是叶子结点 
	if(l < r){
		int mid = (l + r) >> 1;
		if(point <= mid)lt[now] = modify(lt[now],l,mid);//增加的点在目前的左儿子上
		else rt[now] = modify(rt[now], mid + 1, r);//否则在目前的右儿子上

	}
	return now;
}
int query(int u,int v,int l,int r,int k){
	if(l == r)return l;
	int mid = (l + r) >> 1, ans = 0, x = sum[rt[v]] - sum[rt[u]];//x是左子树的全部节点数量
	if(x >= k)ans = query(rt[u], rt[v] , mid + 1, r, k);
	else ans = query(lt[u], lt[v], l, mid, k - x);
	return ans; 
}
int main(){
	int q = 0, l = 0, r = 0, k = 0;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		b[i] = a[i];
	}
	scanf("%d",&m);
	sort(b + 1,b + 1 + n);
	q = unique(b + 1,b + 1 + n) - b - 1;
	build(version[0],1,q);
	for(int i = 1;i <= n;i++){
		point = lower_bound(b + 1, b + 1 + q, a[i]) - b;
		version[i] = modify(version[i - 1], 1, q);
	}
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&l,&r);l++;r++;
		printf("%d\n",b[query(version[l - 1],version[r],1,q,1)]);
	}
	return 0;
}
