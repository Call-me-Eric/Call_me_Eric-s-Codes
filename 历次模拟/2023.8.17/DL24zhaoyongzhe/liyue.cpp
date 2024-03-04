#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
//	int x = 0;scanf("%d",&x);return x;
}
const int maxn = 3e5 + 10;
int n , q, len;
struct query{
	int l, r, id;
	query(int l = 0,int r = 0,int id = 0):l(l),r(r),id(id){}
	friend bool operator < (query a,query b){
		if(a.l / len != b.l / len)return a.l < b.l;
		return ((a.l / len) % 2) ? a.r < b.r : a.r > b.r;
	}
}quest[maxn];
int a[maxn], ans[maxn];
vector<int> edg[maxn];
int sum, buc[maxn];
void add(int x){
	if(!buc[x])
	for(int i = 0;i < edg[x].size();i++){
		sum += buc[edg[x][i]];
	}
	buc[x] ++;
}
void del(int x){
	buc[x]--;
	if(!buc[x])
	for(int i = 0;i < edg[x].size();i++){
		sum -= buc[edg[x][i]];
	}
}
signed main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
//	scanf("%d",&n);len = sqrt(n);
	n = read(); len = sqrt(n);
	for(int i = 1;i <= n;i++){a[i] = read();}
	q = read();
	for(int i = 1;i <= q;i++){
		int u = read(), v = read();
		quest[i] = query(u,v,i);
	}
	for(int i = 1;i * i <= n * 2;i++){
		for(int j = 1;j <= n;j++){
			if(i * i - j > 0){
				edg[j].push_back(i * i - j);
				edg[i * i - j].push_back(j);
			}
		}
	}
	sort(quest + 1,quest + 1 + q);
	int l = 1, r = 0;
	for(int i = 1;i <= q;i++){
		while(l > quest[i].l){add(a[--l]);}
		while(r < quest[i].r){add(a[++r]);}
		while(l < quest[i].l){del(a[l++]);}
		while(r > quest[i].r){del(a[r--]);}
		ans[quest[i].id] = sum / 2;
	}
	for(int i = 1;i <= q;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}

