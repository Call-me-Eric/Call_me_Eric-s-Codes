#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
struct query{
	int l, r, id;
	query(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
	friend bool operator < (query a,query b){return a.r < b.r;}
}quest[maxn];

struct Tree_Array{
	int c[maxn << 1];
	inline int lowbit(int x){return x & (-x);}
	int sum(int x){int ans = 0;for(;x <= n;x += lowbit(x))ans += c[x];return ans;}
	void update(int x,int add){for(;x;x -= lowbit(x))c[x] += add;}
}tree;
int ans[maxn], a[maxn], pos[maxn];
signed main(){
//	freopen("liyue18.in","r",stdin);
//	freopen("liyue.out","w",stdout);
	n  =read();
	for(int i = 1;i <= n;i++){a[i] = read();}
	m = read();
	for(int i = 1;i <= m;i++){
		int u = read(), v = read();
		quest[i] = query(u, v, i);
	}
	sort(quest + 1,quest + 1  + m);
	for(int i = 1, point = 0;i <= m;i++){
		while(point < quest[i].r && point <= n){
			int x = a[++point];
			for(int j = 1;j * j - x <= n;j++){
				if(j * j > x && pos[j * j - x])
					tree.update(pos[j * j - x],1);
			}
			pos[x] = point;
		}
		ans[quest[i].id] = tree.sum(quest[i].l);
	}
	for(int i = 1;i <= m;i++){printf("%d\n",ans[i]);}
	return 0;
}

