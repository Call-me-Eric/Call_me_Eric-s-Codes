#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f;
}
int n,m;
const int maxn = 4e5 + 10;
char ch[maxn];
class Segment_tree{
	private:
	struct node{int ans,right,left;}d[maxn * 4];
	node mergenode(node a,node b){
		node tmp = {0,0,0};int k = min(a.left,b.right);
		tmp.ans = a.ans + b.ans + k;tmp.left = a.left + b.left - k;
		tmp.right = a.right + b.right - k;return tmp;
	}
	void build(int l,int r,int p){
		if(l == r){if(ch[l] == '(')d[p].left += 1;else d[p].right += 1;return;}
		int mid = (l + r) >> 1;build(l,mid,p << 1);build(mid + 1,r,(p << 1) | 1);
		d[p] = mergenode(d[p << 1],d[(p << 1) | 1]);
	}
	node query(int l,int r,int s,int t,int p){
		if(l <= s && t <= r)return d[p];
		int mid = (s + t) >> 1;
		if(mid < l)return query(l,r,mid + 1,t,(p << 1) | 1);
		else if(r <= mid)return query(l,r,s,mid,p << 1);
		else return mergenode(query(l,r,s,mid,p << 1),query(l,r,mid + 1,t,(p << 1) | 1));
	}
	public:
	void build(int n){build(1,n,1);}
	int query(int l,int r){return query(l,r,1,n,1).ans;}
	void DEBUG(){for(int i = 1;i <= n * 4;i++)printf("%d ->ans=%d left=%d right=%d\n",i,d[i].ans,d[i].left,d[i].right);}
}tree;
signed main(){
	scanf("%d%d",&n,&m);
	scanf("%s",ch + 1);int x, y;
	tree.build(n);
	for(int i = 1;i <= m;i++){
		x = read(); y = read();
		printf("%d\n",tree.query(x,y) * 2);
	//	tree.DEBUG();
	}
	return 0;
}
