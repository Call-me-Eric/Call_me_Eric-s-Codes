#include<bits/stdc++.h>
using namespace std;
bool stmemory;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 3e5 + 10;
int n, m;
int fa[21][maxn * 2];
char ch[maxn];
vector<int> edg[maxn * 2];

int head[maxn * 2], id[maxn];
struct Segment_Tree{
	int tot;
	struct node{
		int lc, rc;int sum;
		node(int sum = 0,int lc = 0,int rc = 0):sum(sum),lc(lc),rc(rc){}
	}d[maxn * 30];
	void pushup(int p){d[p].sum = d[d[p].lc].sum + d[d[p].rc].sum;}
	void insert(int l,int r,int &p,int pos){
		if(!p)p = ++tot; d[p].sum++;
		if(l == r)return; int mid = l + r >> 1;
		if(pos <= mid)insert(l,mid,d[p].lc,pos);
		else insert(mid + 1,r,d[p].rc, pos);
		pushup(p);
	}
	int query(int l,int r,int s,int t,int p){
		if(!p)return 0;
		if(s <= l && r <= t)return d[p].sum;
		int mid = l + r >> 1, ans = 0;
		if(s <= mid)ans += query(l,mid,s,t,d[p].lc);
		if(mid < t)ans += query(mid + 1,r,s,t,d[p].rc);
		return ans;
	}
	int merg(int l,int r,int p,int q){
		if(!p || !q)return p | q;
		int x = ++tot;int mid = l + r >> 1;
		d[x].sum = d[p].sum + d[q].sum;
		if(l == r)return x;
		d[x].lc = merg(l,mid,d[p].lc,d[q].lc);
		d[x].rc = merg(mid + 1,r,d[p].rc,d[q].rc);
		return x;
	}
}tree;

struct SAM{
	struct node1{
		int link, len;
		unordered_map<char,int> nxt;
	}d[maxn * 2];
	int tot, last;
	void build(){tot = last = 0;d[0].link = -1;}
	void insert(char ch){
		int cur = ++tot;
		d[cur].len = d[last].len + 1;
		int p = last;
		while(p != -1 && !d[p].nxt[ch]){d[p].nxt[ch] = cur;p = d[p].link;}
		if(p == -1){d[cur].link = 0;}
		else{
			int q = d[p].nxt[ch];
			if(d[p].len + 1 == d[q].len){d[cur].link = q;}
			else{
				int clone = ++tot;
				d[clone].link = d[q].link;
				d[clone].nxt = d[q].nxt;
				d[clone].len = d[p].len + 1;
				while(p != -1 && d[p].nxt[ch] == q){d[p].nxt[ch] = clone;p = d[p].link;}
				d[q].link = d[cur].link = clone;
			}
		}
		last = cur;
	}
	void dfs(int u,int f){
		for(int i = 1;i <= 20;i++){fa[i][u] = (fa[i - 1][u] == -1 ? -1 : fa[i - 1][fa[i - 1][u]]);}
		for(int v : edg[u])
			if(v != f){
				fa[0][v] = u;dfs(v, u);
				head[u] = tree.merg(1,n,head[u],head[v]);
			}
	}
	void init(char *s){
		int len = strlen(s + 1);
		id[0] = 0;build();
		for(int i = 1;i <= len;i++){
			insert(s[i]);id[i] = last;
			tree.insert(1,len,head[last],i);
		}
		for(int i = 1;i <= tot;i++){
			edg[d[i].link].push_back(i);
			edg[i].push_back(d[i].link);
		}
		fa[0][0] = -1;dfs(0, -1);
	}
}sam;
bool check(int mid,int a,int b,int c,int d){
	if(mid == 0)return 1;
	int p = id[c + mid - 1];
	for(int i = 20;i + 1;i--){if(fa[i][p] != -1 && sam.d[fa[i][p]].len >= mid)p = fa[i][p];}
	return tree.query(1,n,a + mid - 1,b,head[p]) > 0;
}
bool edmemory;
signed main(){
	cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost." << endl;
	n = read(); m = read();
	scanf("%s",ch + 1); sam.init(ch);
	while(m--){
		int a = read(), b = read(), c = read(), d = read();
		int l = 0, r = min(b - a + 1,d - c + 1), ans = 0;
		while(l <= r){
			int mid = l + r >> 1;
			if(check(mid,a,b,c,d)){ans = mid,l = mid + 1;}
			else r = mid - 1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
