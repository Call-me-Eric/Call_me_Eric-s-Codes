#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0,f  = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 3e2 + 10;
int n, m;
int a[maxn];
bool ans[maxn][maxn];
bool mo[maxn], vis[maxn];
signed main(){
//#ifndef ONLINE_JUDGE
//	freopen("test.in","r",stdin);
//	freopen("tmp.out","w",stdout);
//#endif
	n = read(); m = read();int mx = 0;
	for(int i = 1;i <= m;i++)mx = max(mx,a[i] = read());
	if(n & 1){
		if(mx > n / 2 + 1){puts("No");return 0;}
		if(mx <= n / 2){
			for(int i = 1;i <= m;i++)
				for(int j = 1;j <= a[i];j++)
					ans[j * 2 - (i & 1)][i] = 1;
			puts("Yes");
			for(int i = 1;i <= n;i++){
				for(int j = 1;j <= m;j++)
					putchar('0' + ans[i][j]);
				putchar('\n');
			}
		}
		else{
			int x = 0;
			queue<int> que;while(!que.empty())que.pop();
			for(int i = 1;i <= m;i++){
				if(a[i] == mx){
					que.push(i);vis[i] = 1;
					for(int j = 1;j <= n;j += 2)ans[j][i] = 1;
					if(x != 0 && i == x + 1){puts("No");return 0;}
				}
			}
			while(!que.empty()){
				int u = que.front();que.pop();vis[u] = 1;
				for(int j = 0;j < 2;j++){
					int v = u + ((j == 0) ? -1 : 1);
					if(v < 1 || v > m || vis[v])continue;
					if(a[v] + a[u] > n / 2 + 1 - mo[u]){
						mo[v] = !mo[u];que.push(v);
					}
				}
			}
			for(int i = 1;i <= m;i++){
				if(a[i] == mx)continue;
				if(i & 1){
					if(!vis[i] && a[i] + a[i - 1] > n / 2 + 1 - mo[i])mo[i] = !mo[i - 1];
					for(int j = 0;j < a[i];j++){
						int x = j * 2 + 1 + mo[i];
						if(ans[x][i - 1] || ans[x][i + 1]){puts("No");return 0;}
						ans[x][i] = 1;
					}
				}
				else{
					if(!vis[i] && a[i] + a[i - 1] > n / 2 + 1 - mo[i])mo[i] = !mo[i - 1];
					for(int j = 0;j < a[i];j++){
						int x = n - mo[i] - j * 2;
						if(ans[x][i - 1] || ans[x][i + 1]){puts("No");return 0;}
						ans[x][i] = 1;
					}
				}
//				for(int j = 1;j <= m;j++)printf("mo[%d] = %d, vis[]= %d\n",j,mo[j],vis[j]);
			}
			puts("Yes");
			for(int i = 1;i <= n;i++){
				for(int j = 1;j <= m;j++)
					putchar('0' + ans[i][j]);
				putchar('\n');
			}
		}
	}
	else{
		if(mx > n / 2){puts("No");return 0;}
		else {
			for(int i = 1;i <= m;i++)
				for(int j = 1;j <= a[i];j++)
					ans[j * 2 - (i & 1)][i] = 1;
			puts("Yes");
			for(int i = 1;i <= n;i++){
				for(int j = 1;j <= m;j++)
					putchar('0' + ans[i][j]);
				putchar('\n');
			}
		}
	}
	return 0;
}
