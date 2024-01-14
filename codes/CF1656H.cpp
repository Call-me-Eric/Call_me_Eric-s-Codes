#include<bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
typedef __int128 ll;
#else
typedef long long ll;
#endif
inline ll read(){
	ll x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x * 10) + (ch - '0');ch = getchar();}
	return x * f;
}
inline void write(ll x){
	stack<char> stk;while(!stk.empty())stk.pop();
	if(x < 0){putchar('-');x = -x;}
	while(x){stk.push((x % 10) + '0');x /= 10;}
	while(!stk.empty()){putchar(stk.top());stk.pop();}
}
const int maxn = 1e3 + 10;
int siz[2], rest[2];ll val[2][maxn];
bool del[2][maxn];
typedef pair<int,int> pii;

struct Segment_Tree{
	ll d[maxn << 2], x;int opt;
	void build(int l,int r,int p){
		if(l == r){d[p] = x / __gcd(val[opt][l],x);return;}
		int mid = (l + r) >> 1;
		build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
		d[p] = __gcd(d[p << 1],d[p << 1 | 1]);
	}
	void delet(int l,int r,int pos,int p){
		if(l == r && l == pos){d[p] = 0;return;}
		int mid = (l + r) >> 1;
		if(pos <= mid)delet(l,mid,pos,p << 1);
		else delet(mid + 1,r,pos,p << 1 | 1);
		d[p] = __gcd(d[p << 1],d[p << 1 | 1]);
	}
	ll getans(){return d[1];}
}tree[2][maxn];

void solve(){
	rest[0] = siz[0] = read();rest[1] = siz[1] = read();
	for(int j = 0;j < 2;j++)
		for(int i = 1;i <= siz[j];i++){
			val[j][i] = read();
			del[j][i] = 0;
		}
	queue<pii> que;
	for(int j = 0;j < 2;j++){
		for(int i = 1;i <= siz[j];i++){
			tree[j][i].x = val[j][i];tree[j][i].opt = (j ^ 1);
			tree[j][i].build(1,siz[j ^ 1],1);
			if(tree[j][i].getans() > 1){
				del[j][i] = 1;que.push(make_pair(j,i));rest[j]--;
			}
		}
	}
	while(!que.empty()){
		int opt = que.front().first, pos = que.front().second;que.pop();
		for(int i = 1;i <= siz[opt ^ 1];i++){
			if(!del[opt ^ 1][i]){
				tree[opt ^ 1][i].delet(1,siz[opt],pos,1);
				if(tree[opt ^ 1][i].getans() > 1){
					del[opt ^ 1][i] = 1;que.push(make_pair(opt ^ 1,i));rest[opt ^ 1]--;
				}
			}
		}
	}
	if(!rest[0] || !rest[1]){puts("NO");return;}
	printf("YES\n%d %d\n",rest[0],rest[1]);
	for(int j = 0;j < 2;j++){
		for(int i = 1;i <= siz[j];i++){
			if(!del[j][i]){write(val[j][i]);putchar(' ');}
		}
		puts("");
	}
}
signed main(){
	int T = read();
	while(T--)solve();
	return 0;
}
