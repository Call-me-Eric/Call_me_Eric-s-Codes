#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 5e3 + 10;
int n;
int a[maxn][maxn];
int f[maxn][maxn];
bool flag[maxn][maxn][2];
queue<pair<int,int> > que;
signed main(){
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			a[i][j] = read();
			if(f[i - 1][j] > f[i][j - 1]){
				f[i][j] = f[i - 1][j] + a[i][j];
				flag[i - 1][j][1] = 1;
			}
			else{
				f[i][j] = f[i][j - 1] + a[i][j];
				flag[i][j - 1][0] = 1;
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			ans += f[i][j];
		}
	}
	printf("%lld\n",ans);
	char opt;int x, y;
	for(int i = 1;i <= n;i++){
		opt = getchar();x = read(); y = read();
		if(opt == 'U')a[x][y]++;
		else a[x][y]--;
		for(int i = x;i <= n;i++){
			for(int j = y;j <= n;j++){
				ans -= f[i][j];
				f[i][j] = max(f[i - 1][j],f[i][j - 1]) + a[i][j];
				ans += f[i][j];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

