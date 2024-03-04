#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 110, maxk = 20;
int n, k;
int f[maxn][maxn][maxk];
int a[maxn][maxn];
priority_queue<int> que;
signed main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	n = read(); k = read();
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++)
			a[i][j] = read();
	for(int i = 2;i <= k;i++){f[1][1][i] = -0x3f3f3f3f3f;}
	f[1][1][1] = a[1][1];
	for(int i = 2;i <= n;i++){
		for(int j = 1;j <= i;j++){
			while(!que.empty())que.pop();
			for(int l = 1;l <= k;l++){
				if(j != i)que.push(f[i - 1][j    ][l]);
				if(j != 1)que.push(f[i - 1][j - 1][l]);
			}
			for(int l = 1;l <= k;l++){
				f[i][j][l] = que.top() + a[i][j];
				que.pop();
			}
		}
	}
	while(!que.empty())que.pop();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= k;j++){
			que.push(f[n][i][j]);
		}
	}
//	for(int i = 1;i <= 10;i++){printf("%lld\n",que.top());que.pop();}
	for(int i = 1;i < k;i++){que.pop();}
	printf("%lld\n",que.top());
	return 0;
}

