#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f =1 ;char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
const int maxn = 2e3 + 10;
int n, m, K;
struct lines{
	int l, r;
	lines(int l = 0,int r = 0):l(l),r(r){}
	friend bool operator < (lines a,lines b){return a.l != b.l ? a.l < b.l : a.r > b.r;}
}a[maxn], b[maxn];
int f[maxn][maxn];
class Segment_Tree{
private:
	struct node{
		int mx;
		node(int mx = 0):mx(mx){}
	}d[maxn << 2];
	node mergenode(node l,node r){return node(max(l.mx,r.mx));}
	void update(int l,int r,int goal,int p,int add){
		if(l == r && l == goal){d[p] = node(add);return;}
		int mid = l + r >> 1;
		if(goal <= mid)update(l,mid,goal, p<< 1,add);
		else update(mid + 1,r,goal, p << 1 | 1,add);
		d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
	}
	node query(int l,int r,int s,int t,int p){
		if(s <= l && r <= t){return d[p];}
		int mid = l + r >> 1;
		if(t <= mid)return query(l,mid,s,t,p << 1);
		if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
		return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
	}
public:
	void update(int goal,int add){update(1,n,goal,1,add);}
	int query(int s,int t){if(s > t)return 0;return query(1,n,s,t,1).mx;}
}tree[maxn][2];
signed main(){
	freopen("stamps.in","r",stdin);
	freopen("stamps.out","w",stdout);
	n = read(); m = read(); K = read(); int u, v, tot = 0;
	for(int i = 1;i <= m;i++){u = read(); v = read(); a[i] = lines(u, v);}
	sort(a + 1,a + 1 + m);u = v = 0;
	for(int i = 1;i <= m;i++){
		if(a[i].r > v){b[++tot] = a[i];u = a[i].l, v = a[i].r;}
	}
	sort(b + 1,b + 1 + tot);
//	for(int i = 1;i <= tot;i++){
//		printf("%d----%d\n",b[i].l,b[i].r);
//	}
	bool switchcase = (n > 200);
	int ans = 0;
	for(int i = 1;i <= tot;i++){
		f[b[i].l][1] = b[i].r - b[i].l + 1;
		ans = max(ans,f[b[i].l][1]);
	if(switchcase){
		tree[1][0].update(b[i].l,f[b[i].l][1]);
		tree[1][1].update(b[i].l,f[b[i].l][1] + b[i].l);
	}
	}
	for(int k = 2;k <= K;k++){
		for(int i = tot;i >= 1;i--){
		if(switchcase){
				f[b[i].l][k] = max(f[b[i].l][k],
							max(tree[k - 1][0].query(b[i].r + 1,n) + (b[i].r - b[i].l + 1),
							tree[k - 1][1].query(b[i].l + 1,b[i].r) - b[i].l));
				tree[k][0].update(b[i].l,f[b[i].l][k]);
				tree[k][1].update(b[i].l,f[b[i].l][k] + b[i].l);
		}
		else{
			for(int j = b[i].l + 1;j <= n;j++){
				f[b[i].l][k] = max(f[b[i].l][k] , f[j][k - 1] + (min(j - 1,b[i].r) - b[i].l + 1));
			}
		}
			ans = max(ans,f[b[i].l][k]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
