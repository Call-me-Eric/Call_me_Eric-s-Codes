#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define eps 0.00000001
#define ll long long
#define orz puts("--------------------------")
#define pf(x) printf("%s",x);
#define pii pair<int,int>
#define pb push_back
#define mk make_pair
#define newline puts("")
#define newspace putchar(' ')
#define lowbit(x) (x&(-x))
#define md(l,r) ((l+r)>>1)
#define lson(p) (p<<1)
#define rson(p) ((p<<1)|1)
#define ls(p) (t[p].ls)
#define rs(p) (t[p].rs)
#define fi first
#define se second
#define inf 2147483647
#define mod 1000000007
#define N 1000010

namespace fastIO{
	template<typename T> void read(T &x){
		x=0;
		char ch=getchar();T fl=1;
		while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();};
		while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();};
		x=x*fl;
	}
	template<typename T, typename ...T1> void read(T &x, T1 &...x1){
		read(x);
		read(x1...);
	}
	template<typename T> void write(T x){
		if(x<0){
			x=-x;putchar('-');
		}
		if(x/10)write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void writer(T x){
		write(x);
		putchar(' ');
	}
	template<typename T> void writen(T x){
		write(x);
		putchar('\n');
	}
}

using namespace fastIO;

int n, m, q;
int w[N];
int stk[30], top;
int que[30], cnt;
int f[30][30];

signed main() {
freopen("andgraph.in","r",stdin);
	freopen("andgraph.out","w",stdout);

	read(n, m, q);
	memset(f, 0x3f, sizeof(f));
	int INF = f[0][0];
	for (int i = 1; i <= n; i++) {
		read(w[i]);
		top = 0;
		for (int j = 0; j <= 20; j++) {
			if (w[i] & (1 << j)) stk[++top] = j;
		}
		for (int j = 1; j <= top; j++) {
			for (int k = j + 1; k <= top; k++) {
				int u = stk[j], v = stk[k];
				f[u][v] = min(f[u][v], 2 * w[i]);
				f[v][u] = min(f[v][u], 2 * w[i]);
			}
		}
	}
	for (int i = 0; i <= 20; i++) f[i][i] = 0;
	for (int k = 0; k <= 20; k++) {
		for (int i = 0; i <= 20; i++) {
			for (int j = 0; j <= 20; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	while (q--) {
		int s, t;
		read(s, t);
		top = cnt = 0;
		for (int i = 0; i <= 20; i++) {
			if (w[s] & (1 << i)) stk[++top] = i;
			if (w[t] & (1 << i)) que[++cnt] = i;
		}
		int ans = INF;
		for (int i = 1; i <= top; i++) {
			for (int j = 1; j <= cnt; j++) {
				ans = min(ans, f[stk[i]][que[j]]);
			}
		}
		if (ans == INF) puts("-1");
		else writen(ans + w[s] + w[t]);
	}
	return 0;
}