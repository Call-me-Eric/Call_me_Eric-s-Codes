#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm> 
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
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
	sum[now] = sum[history] + 1;//�����Ҷ�ӽ�� 
	if(l < r){
		int mid = (l + r) >> 1;
		if(point <= mid)lt[now] = modify(lt[now],l,mid);//���ӵĵ���Ŀǰ���������
		else rt[now] = modify(rt[now], mid + 1, r);//������Ŀǰ���Ҷ�����

	}
	return now;
}
int query(int u,int v,int l,int r,int k){
	if(l == r)return l;
	int mid = (l + r) >> 1, ans = 0, x = sum[lt[v]] - sum[lt[u]];//x����������ȫ���ڵ�����
	if(x >= k)ans = query(lt[u], lt[v] ,l, mid, k);
	else ans = query(rt[u], rt[v], mid + 1, r, k - x);
	return ans; 
}
signed main(){
	int q = 0, l = 0, r = 0, k = 0;
	n = read(); m = read();
	for(int i = 1;i <= n;i++){
		a[i] = read();
		b[i] = a[i];
	}
	sort(b + 1,b + 1 + n);
	q = unique(b + 1,b + 1 + n) - b - 1;
	build(version[0],1,q);
	for(int i = 1;i <= n;i++){
		point = lower_bound(b + 1, b + 1 + q, a[i]) - b;
		version[i] = modify(version[i - 1], 1, q);
	}
	for(int i = 1;i <= m;i++){
		l = read(); r = read(); k = read();
		printf("%d\n",b[query(version[l - 1],version[r],1,q,k)]);
	}
	return 0;
}

