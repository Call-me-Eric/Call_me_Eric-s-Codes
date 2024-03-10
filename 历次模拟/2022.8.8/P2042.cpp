#include<iostream>
#include<stdio.h>
#include<string.h>
#define TT int
using namespace std;
inline TT read(){
	TT x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
const int N = 5e5 + 10;
long long n, m;
long long a[N];
class Splay{
public:
	long long tot, root, tot2, s[N];
	struct tree_Splay{
		int fa, child[2], size;
		long long val, sum, maxn, lazy, tag, ls, rs;
		bool laz;
	}t[N];
	void down(int k){
		int l = t[k].child[0], r = t[k].child[1];
		if(t[k].laz){
			t[k].lazy = t[k].laz = 0;
			if(l){
				t[l].laz = true;
				t[l].val = t[k].val;
				t[l].sum = t[k].val * t[k].size;
			}
			if(r){
				t[r].laz = true;
				t[r].val = t[k].val;
				t[r].sum = t[k].val * t[k].size;
			}
			if(t[k].val >= 0){
				if(l){
					t[l].ls = t[l].rs = t[l].maxn = t[l].sum;
				}
				if(r){
					t[r].ls = t[r].rs = t[r].maxn = t[r].sum;
				}
			}
			else {
				if(l){
					t[l].ls = t[l].rs = 0;t[l].maxn = t[k].val;
				}
				if(r){
					t[r].ls = t[r].rs = 0;t[r].maxn = t[k].val;
				}
			}
		}
		if(t[k].tag){
			t[k].tag = 0; t[l].tag ^= 1; t[r].tag ^= 1;
			swap(t[l].ls,t[l].rs); swap(t[r].ls,t[r].rs);
			swap(t[l].child[0],t[l].child[1]);
			swap(t[r].child[0],t[r].child[1]);
		}
	}
	void up(int k){
		int l = t[k].child[0], r = t[k].child[1];
		t[k].size = t[l].size + t[r].size + 1;
		t[k].sum = t[l].sum + t[k].val + t[r].sum;
		t[k].maxn = max(max(t[l].maxn,t[r].maxn),t[l].rs + t[k].val + t[r].ls);
		t[k].ls = max(t[l].ls,t[l].sum + t[k].val + t[r].ls);
		t[k].rs = max(t[r].rs,t[r].sum + t[k].val + t[l].rs);
	}
	bool get(int k){
		return t[t[k].fa].child[1] == k;
	}
	void rotate(int k){
		int fa = t[k].fa, pa = t[fa].fa;
		int d1 = get(k), d2 = get(fa);
		t[fa].child[d1] = t[k].child[d1 ^ 1];
		t[t[k].child[d1 ^ 1]].fa = fa;
		t[fa].fa = k;
		t[k].child[d1 ^ 1] = fa;
		t[k].fa = pa;
		t[pa].child[d2] = k;
		up(fa); up(k);
	}
	void splay(int x,int y){
		while(t[x].fa != y){
			int fa = t[x].fa,pa = t[fa].fa;
			int d1 = get(x), d2 = get(fa);
			if(pa != y){
				if(d1 == d2)rotate(fa);
				else rotate(x);
			}
			rotate(x);
		}
		if(!y)root = x;
	}
	int kth(int k){
		int now = root;
		while(1){
			down(now);
			if(k <= t[t[now].child[0]].size) now = t[now].child[0];
			else if(k == t[t[now].child[0]].size)return now;
			else {
				k -= t[t[now].child[0]].size;
				now = t[now].child[1];
			}
		}
	}
	int build(int l,int r,int fa){
		if(l > r)return 0;
		int mid = (l + r) >> 1, now = 0;
		if(tot2) now = s[tot2]--;
		else now = ++tot;
		t[now].fa = fa;
		t[now].val = a[mid];
		t[now].tag = t[now].laz = t[now].lazy = 0;
		t[now].child[0] = build(l, mid - 1, now);
		t[now].child[1] = build(mid + 1, r, now);
		up(now);
		return now;
	}
	void insert(int l,int x){
		int r = l + 1;
		l = kth(l + 1);	r = kth(r + 1);
		splay(l, 0);	splay(r, l);
		for(int i = 1;i <= x;i++)a[i] = read();
		t[r].child[0] = build(1,x,r);
		n += x;
		up(r);	up(l);
	}

	void erase(int k){
		if(!k)return;
		s[++tot2] = k;
		erase(t[k].child[0]);
		erase(t[k].child[1]);
	}

	void delet(int l,int r){
		n -= r - l + 1;
		l = kth(l);	r = kth(r + 2);//(l + 1)-1 = l,(r + 1) + 1 = r + 2
		splay(l,0);	splay(r,l);
		erase(t[r].child[0]);
		t[r].child[0] = 0;
		up(r);	up(l);
	}
	
	void make_same(int l,int r,int x){
		l = kth(l);r = kth(r + 2);
		splay(l, 0);splay(r,l);
		int k = t[r].child[0];
	    t[k].val = x;
		t[k].sum = t[k].size * x;
		if(x <= 0)t[k].ls = t[k].rs = 0,t[k].maxn = x;
		else t[k].ls = t[k].rs = t[k].maxn = t[k].size * x;
		t[k].lazy = x;
		t[k].laz = true;
		up(r);	up(l);
	}

	void reverse(int l,int r){
		l = kth(l);	r = kth(r + 2);
		splay(l,0);	splay(r,l);
		int k = t[r].child[0];
		if(!t[k].laz){
			t[k].tag ^= 1;
			swap(t[k].child[0],t[k].child[1]);
			swap(t[k].ls,t[k].rs);
			up(r);	up(l);
		}
	}
}splay;
signed main(){
	n = read(); m = read();
	splay.t[0].maxn = -0x3f3f3f3f;
	a[1] = -0x3f3f3f3f;
	a[n + 2] = -0x3f3f3f3f;
	for(int i = 2;i <= n + 1;i++)a[i] = read();
	root = splay.build(1,n + 2,0);
	while(m--){
		char ch[9];
		int x, y, z;
		scanf("%s",ch);
	}
	return 0;
}

