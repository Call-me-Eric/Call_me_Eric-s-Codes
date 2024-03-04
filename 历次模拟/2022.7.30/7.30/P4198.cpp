#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n, m;
const int maxn = 1e5 + 10;
struct Tree{
	int ans;
	double mx;
}tree[maxn * 4];
double a[maxn];
int pushup(double mx, int x,int l,int r){
	if(tree[x].mx <= mx)return 0;
	if(a[l] > mx)return tree[x].ans;
	if(l == r)return a[l] > mx;
	int mid = (l + r) >> 1;
	if(tree[x << 1].mx <= mx)return pushup(mx,x << 1 | 1,mid + 1,r);
	else return pushup(mx,x << 1,l,mid) + tree[x].ans - tree[x << 1].ans;
}
void update(int x,int l,int r,int to,int c){
	if(l == r && l == to){
		tree[x].mx = 1.0 * c / to;
		tree[x].ans = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(to <= mid)update(x << 1,l,mid,to,c);
	else if(to > mid)update(x << 1 | 1,mid + 1,r,to,c);
	tree[x].mx = max(tree[x << 1].mx,tree[x << 1 | 1].mx);
	tree[x].ans = tree[x << 1].ans + pushup(tree[x << 1].mx,x << 1 | 1,mid + 1,r);
}
signed main(){
	scanf("%d%d",&n,&m);
	int x, y;
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		a[x] = 1.0 * y / x;
		update(1,1,n,x,y);
		printf("%d\n",tree[1].ans);
	}
	return 0;
}

