#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2e5 + 10;
struct node{
	int x, y, id;
	node(int x = 0,int y = 0,int id = 0):x(x),y(y),id(id){}
	friend bool operator < (node a,node b){
		if(a.x != b.x)return a.x < b.x;
		if(a.y != b.y)return a.y < b.y;
		return a.id < b.id;
	}
}a[maxn],b[maxn], c[maxn];
struct cmp{
	bool operator ()(node a,node b){
		if(a.y != b.y)return a.y < b.y;
		return a.x < b.x;
	}
};
int n, m, C, H;
inline int Abs(int x){return x < 0 ? -x : x;}
int cnt[maxn];
int dist(int i,int j){return Abs(c[i].x - c[j].x) + Abs(c[i].y - c[j].y);}

signed main(){
	freopen("theatre.in","r",stdin);
	freopen("theatre.out","w",stdout);
	C = read(); H = read();int u, v;
	n = read();
	for(int i = 1;i <= n;i++){
		u = read(); v = read();
		a[i] = node(u, v, i);
	}
	m = read();
	for(int i = 1;i <= m;i++){
		u = read(); v = read();
		b[i] = node(u, v, i);
	}
	if(n <= 5e3 && m <= 5e3){
		sort(a + 1,a + 1 + n);
		sort(b + 1,b + 1 + m);
		int ans = 0x3f3f3f3f3f, id = 0;
		for(int i = 1;i <= m;i++){
			int res = 0;
			for(int j = 1;j <= n;j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			if(ans > res){
				ans = res;
				id = b[i].id;
			}
		}
		printf("%lld\n%lld\n",ans,id);
	}
	else{
		srand(time(0));
		sort(a + 1,a + 1 + n);
		int ans = 0x3f3f3f3f3f3f3f, id = 0;
		for(int i = 1;i <= m;i++){
			int res = 0;
			for(int j = 1;j <= min(n,100ll);j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			for(int j = max(1ll,n - 100);j <= n;j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			cnt[i] = res;
		}
		sort(a + 1,a + 1 + n,cmp());
		for(int i = 1;i <= m;i++){
			int res = 0;
			for(int j = 1;j <= min(n,100ll);j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			for(int j = max(1ll,n - 100);j <= n;j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			cnt[i] = res;
		}
		random_shuffle(b + 1,b + 1 + m);
		for(int test = 1;test <= 50;test++){
			int i = rand() * rand() / test % n + 1;
			int res = 0;
			for(int j = 1;j <= n;j++)
				res = max(res,Abs(b[i].x - a[j].x) + Abs(b[i].y - a[j].y));
			cnt[b[i].id] = res;
		}
		for(int i = 1;i <= n;i++){
			if(ans > cnt[b[i].id]){
				ans = cnt[b[i].id];
				id = b[i].id;
			}
		}
		printf("%lld\n%lld\n",ans,id);
	}
	return 0;
}
