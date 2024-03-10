#include<bits/stdc++.h>
#define pdi pair<double,int>
using namespace std;
const int mod1 = 39989,mod2 = 1e9 + 1,maxn = 1e5 + 10;
int lastans, n, op;
struct Line{
	double k, b;
}p[maxn];
int s[maxn * 4];
int cnt;
double calc(int id,int d){
	return p[id].b + p[id].k * d;
}
void add(int x2,int y2,int x1,int y1){
	cnt++;
	if(x2 == x1){
		p[cnt].k = 0;p[cnt].b = max(y1,y2);
	}
	else {
		p[cnt].k = 1.0 * (y1 - y2) / (x1 - x2);
		p[cnt].b = y2 * 1.0 - p[cnt].k * x2;
	}
	return;
}
void upd(int root,int l,int r,int u){
	int mid = (l + r) >> 1;
	if(calc(u,mid) > calc(s[root],mid))swap(u,s[root]);
	if(calc(u,l) > calc(s[root],l))upd(root << 1,l,mid,u);
	if(calc(u,r) > calc(s[root],r))upd(root << 1 | 1,mid + 1,r,u);
}
void update(int root,int cl,int cr,int l,int r,int u){
	if(l <= cl && r >= cr){
		upd(root,cl,cr,u);
		return;
	}
	int mid = (cl + cr) >> 1;
	if(l <= mid)update(root << 1,cl,mid,l,r,u);
	if(mid < r)update(root << 1 | 1,mid + 1,cr,l,r,u);
}
pdi pmax(pdi x,pdi y){
	if(x.first < y.first)return y;
	else if(x.first > y.first)return x;
	else return x.second < y.second ? x : y;
}
pdi query(int root,int l,int r,int d){
	if(r < d || l > d)return {0,0};
	int mid = (l + r) >> 1;
	double ans = calc(s[root],d);
	if(l == r)return {ans,s[root]};
	return pmax({ans,s[root]},pmax(query(root << 1,l,mid,d),query(root << 1 | 1,mid + 1,r,d)));
}
signed main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&op);
		if(op){
			int x1,y1,x2,y2;
			double k = 0, b = 0;
			scanf("%d%d%d%d",&x2,&y2,&x1,&y1);
			x2 = (x2 + lastans - 1) % mod1 + 1;
			y2 = (y2 + lastans - 1) % mod2 + 1;
			x1 = (x1 + lastans - 1) % mod1 + 1;
			y1 = (y1 + lastans - 1) % mod2 + 1;
			if(x2 > x1){
				swap(x2,x1);swap(y2,y1);
			}
			add(x2,y2,x1,y1);
			update(1,1,mod1,x2,x1,cnt);
		}
		else {
			int x;
			scanf("%d",&x);
			x = (x + lastans - 1 + mod1) % mod1 + 1;
			lastans = query(1,1,mod1,x).second;
			printf("%d\n",lastans);
		}
	}
	return 0;
}

