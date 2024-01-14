#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
bool st;
const int maxn = 3e6 + 10,maxm = 1e5 + 10;
int ch[maxn][2], tot = 1;
int tim[maxn];
inline bool leaf(int p){return !ch[p][0] && !ch[p][1];}
void pushdown(int p){
	if(!ch[p][0])ch[p][0] = ++tot;
	if(!ch[p][1])ch[p][1] = ++tot;
	if(tim[p]){
		tim[ch[p][0]] = tim[ch[p][1]] = tim[p];
		tim[p] = 0;
	}
}
void insert(ll l,ll r,ll s,ll t,int p,int tim){
	if(r < s || t < l)return;
	if(s <= l && r <= t){::tim[p] = tim;return;}
	ll mid = l + r >> 1;pushdown(p);
	if(s <= mid)insert(l,mid,s,t,ch[p][0],tim);
	if(mid < t)insert(mid + 1,r,s,t,ch[p][1],tim);
}
vector<pair<int,int> > edg[maxm];
void addedg(int x,int y){
	if(leaf(x) && leaf(y)){edg[min(tim[x],tim[y])].push_back(make_pair(x, y));return;}
	if(leaf(x)){addedg(x,ch[y][0]);addedg(x,ch[y][1]);return;}
	if(leaf(y)){addedg(ch[x][0],y);addedg(ch[x][1],y);return;}
	addedg(ch[x][0],ch[y][0]);addedg(ch[x][1],ch[y][1]);
}
int getpos(ll l,ll r,ll pos,int p){
	if(leaf(p)){return p;}
	ll mid = l + r >> 1;
	if(pos <= mid)return getpos(l,mid,pos,ch[p][0]);
	else return getpos(mid + 1,r,pos,ch[p][1]);
}
ll n, m;
pair<pair<ll,ll>, bool> qry[maxm];

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
void merg(int x,int y){fa[getf(x)] = getf(y);}
bool ed;
signed main(){
	cerr << (&st - &ed) / 1024.0 / 1024.0 << "Mib cost." << endl;
	n = read(); m = read();n = (1LL << n) - 1;
	tim[1] = m + 1;
	for(int i = 1;i <= m;i++){
		char opt[10];scanf("%s",opt);
		ll x = read(), y = read();
		if(opt[0] == 'b'){insert(0,n,x,y,1,i);qry[i].second = 0;}
		else qry[i].second = 1;
		qry[i].first = make_pair(x, y);
	}
	for(int i = 1;i <= tot;i++){
		if(!leaf(i))addedg(ch[i][0],ch[i][1]);
		fa[i] = i;
	}
	for(auto i : edg[m + 1]){merg(i.first,i.second);}
	stack<bool> stk;while(!stk.empty())stk.pop();
	for(int i = m;i;i--){
		for(auto j : edg[i]){merg(j.first,j.second);}
		if(qry[i].second){
			stk.push(getf(getpos(0,n,qry[i].first.first,1)) == getf(getpos(0,n,qry[i].first.second,1)));
//			printf("%lld %lld %lld %lld\n",getpos(0,n,qry[i].first.first,1),getpos(0,n,qry[i].first.second,1),
//				getf(getpos(0,n,qry[i].first.first,1)),getf(getpos(0,n,qry[i].first.second,1)));
		}
	}
//	for(int i = 0;i <= m + 1;i++)
//		printf("siz[%lld] = %d\n",i,edg[i].size());
	while(!stk.empty()){putchar('0' + stk.top());stk.pop();putchar('\n');}
	return 0;
}
