#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

const int N=2e3+5;

int n, m, a[N][N];
int same[N][N], touch[N][N], len1[N][N], len2[N][N];
/*
(i,j) 第一次遇到相同颜色最长的距离 拉链能拉到的最长的地方 拉链的长度 
*/
int pre[N*N];

void calc(int sx, int sy){
	for(int k=1; sx-k+1>0 && sy+k-1<=m; k++){
		int x=sx-k+1, y=sy+k-1;
		len2[x][y]=k-pre[a[x][y]];
		pre[a[x][y]]=k;
	}
	for(int k=1; sx-k+1>0 && sy+k-1<=m; k++){
		int x=sx-k+1, y=sy+k-1;
		pre[a[x][y]]=0;
	}
}

inline void init(){
	for(int j=1; j<=m; j++){
		for(int i=1; i<=n; i++){
			same[i][j]=(pre[a[i][j]]? pre[a[i][j]]:0);
			pre[a[i][j]]=i;
		}
		for(int i=1; i<=n; i++) pre[a[i][j]]=0;
		for(int i=1; i<=n; i++){
			touch[i][j]=(i==1? 1:touch[i-1][j]);
			if(i!=1 && j!=1 && a[i][j]!=a[i-1][j-1]) touch[i][j]=i;
			len1[i][j]=i-max(touch[i][j], same[i][j]+1)+1;
		}
	}
	for(int i=1; i<=n; i++) calc(i, 1);
	for(int i=2; i<=m; i++) calc(n, i);
}

int stk[N], tp;
bool vis[N*N];

inline int solve(){
	int ans=n;
	for(int i=1; i<=n; i++){
		for(int j=2; j<=m; j++){
			int len=1, lim=0, k, premn;
			vis[a[i][j]]=1;
			for(k=1, premn=INT_MAX; i>k && j>k; k++){
				if(vis[a[i][j-k]] || vis[a[i-k][j]]) break;
				premn=min(premn, len1[i][j-k+1]);
				if(premn<k+1) break;
				len=k+1;
				vis[a[i][j-k]]=vis[a[i-k][j]]=1;
			}
			ans+=len;
			vis[a[i][j]]=0;
			for(int x=1; x<=k; x++) vis[a[i][j-x]]=vis[a[i-x][j]]=0;
		}
	}
	printf("%lld\n", ans);
}

signed main(){
	freopen("rainbow.in", "r", stdin);
	freopen("rainbow.out", "w", stdout);
	n=rd(), m=rd();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			a[i][j]=rd();
		}
	}
	init();
	solve();
	return 0;
}
