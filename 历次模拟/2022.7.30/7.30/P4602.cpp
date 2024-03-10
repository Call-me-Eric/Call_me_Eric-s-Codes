#include<iostream>
#include<stdio.h>
#include<algorithm>
#define int long long
using namespace std;
int n, m, size_tree = 0,dmax = 0;
const int maxn = 100000 + 10;
struct node{
	int delicious, price, limit;
}a[maxn];
struct cmp{
	bool operator () (node a, node b ){
		return a.delicious < b.delicious;
	}
};
struct Tree{
	int l, r, litre, price;
}tree[maxn * 20];
int version[maxn];
int point;
int modify(int history,int l,int r,int pri,int lim){
	int now = ++size_tree;
	tree[now].l = tree[history].l;
	tree[now].r = tree[history].r;
	tree[now].price += tree[history].price + lim * pri;
	tree[now].litre += tree[history].litre + lim;
	if(l == r) return now;
	int mid = (l + r) >> 1;
	if(mid >= pri) tree[now].l = modify(tree[now].l,l,mid,pri,lim);//增加的点在目前的左儿子上
		else tree[now].r = modify(tree[now].r, mid + 1, r, pri, lim);//否则在目前的右儿子上
	return now;
}
int query(int u,int v,int l,int r,int lit){
	if(l == r)return lit * l;
	int mid = (l + r) >> 1, ans = 0, x = tree[tree[v].l].litre - tree[tree[u].l].litre;//x是左子树的全部节点数量
	if(x > lit)ans = query(tree[u].l, tree[v].l ,l, mid, lit);
	else if(x == lit)return tree[tree[v].l].price - tree[tree[u].l].price;
	else ans = tree[tree[v].l].price - tree[tree[u].l].price + query(tree[u].r, tree[v].r, mid + 1, r, lit - x);
	return ans;
}

int solve(int g,int L){
	int l = 1,r = n,mid = 0, ans = -1;
	while(l <= r){
		mid = (l + r) >> 1;
		if(query(version[mid - 1],version[n],1,dmax,L) <= g && tree[version[n]].litre - tree[version[mid - 1]].litre >= L)l = mid + 1,ans = mid;
		else r = mid - 1;
	}
	if(ans == -1)return -1;
	else return a[ans].delicious;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld%lld",&a[i].delicious,&a[i].price,&a[i].limit);
		dmax = max(a[i].price,dmax);
	}
	sort(a + 1,a + 1 + n,cmp());
	for(int i = 1;i <= n;i++){
		version[i] = version[i - 1];
		version[i] = modify(version[i - 1], 1, dmax,a[i].price,a[i].limit);
	}
	int g, l;
	for(int i = 1;i <= m;i++){
		scanf("%lld%lld",&g,&l);
		printf("%lld\n",solve(g,l));
	}
	return 0;
}

