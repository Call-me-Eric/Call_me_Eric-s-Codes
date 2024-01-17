#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 510, mod = 998244353;
int n, a[maxn][maxn], q;
long long f[maxn][maxn];

struct node{
	int first, second;
	node(int f = 0,int s = 0):first(f),second(s){}
	friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
	friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
};
struct node1{
	int first;node second;
	node1(int f = 0,node s = node()):first(f),second(s){}
	friend bool operator < (node1 a,node1 b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
	friend bool operator > (node1 a,node1 b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
}b[maxn * maxn];int tot;

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = { 0,-1, 1, 0};

signed main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++){
			a[i][j] = read();
			b[++tot] = node1(a[i][j],node(i,j));
		}
	sort(b + 1,b + 1 + tot);
	q = read(); int x, y;
	for(int qry = 1;qry <= q;qry++){
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)f[i][j] = 1;
		x = read(); y = read();long long ans = 0;
		int tmp = a[x][y]; a[x][y] = 0x3f3f3f3f;
		for(int i = 1;i <= tot;i++){
			int u = b[i].second.first, v = b[i].second.second;
			if(u == x && v == y)continue;
			long long cnt = 1;
			for(int k = 0;k < 4;k++){
				int nx = u + dx[k], ny = v + dy[k];
				if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
				if(a[nx][ny] <= a[u][v])cnt++;
				if(a[nx][ny] >= a[u][v])continue;
				f[u][v] = (f[u][v] + f[nx][ny]) % mod;
			}
			ans = (ans + f[u][v] * cnt % mod) % mod;
		}
		int u = x, v = y;
		for(int k = 0;k < 4;k++){
			int nx = u + dx[k], ny = v + dy[k];
			if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
			if(a[nx][ny] >= a[u][v])continue;
			f[u][v] = (f[u][v] + f[nx][ny]) % mod;
		}
		a[u][v] = tmp; ans = (ans + f[u][v]) % mod;
//		for(int i = 1;i <= n;i++){
//			for(int j = 1;j <= n;j++)
//				printf("f[%d][%d]=%lld ",i,j,f[i][j]);
//			puts("");
//		}
		printf("%lld\n",ans);
	}
	return 0;
}
