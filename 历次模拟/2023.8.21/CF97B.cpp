#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0 , f = 1;char ch  =getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
struct node{
	int x, y;
	node(int x = 0,int y = 0):x(x),y(y){}
	friend bool operator < (node a,node b){return a.x == b.x ? a.y < b.y : a.x < b.x;}
	friend bool operator ==(node a,node b){return a.x == b.x && a.y == b.y;}
}a[maxn * 2];
int tot;
void solve(int l,int r){
	if(l == r)return;
	int mid = (l + r) >> 1;
	for(int i = l;i <= r;i++)
		a[++tot] = node(a[mid].x,a[i].y);
	solve(l,mid); solve(mid + 1,r);
}
signed main(){
	n = read();
	for(int i = 1;i <= n;i++){
		a[i].x = read();a[i].y = read();
	}
	sort(a + 1,a + 1 + n);
	tot = n;
	solve(1,n);
	sort(a + 1, a + 1 + tot);
	m = unique(a + 1,a +1 + tot) - a - 1;
	printf("%d\n",m);
	for(int i = 1;i <= m;i++){
		printf("%d %d\n",a[i].x,a[i].y);
	}
	return 0;
}
