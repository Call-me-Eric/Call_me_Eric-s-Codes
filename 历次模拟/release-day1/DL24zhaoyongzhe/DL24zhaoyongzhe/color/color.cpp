#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 3e5 + 10;

int n, m;
vector<int> edg[maxn];
bool book[maxn], reach[maxn];
int to[maxn], tmp[maxn];

signed main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n = read(); m = read();
	for(int i = 1;i <= m;i++){
		int u = read(), v = read();
		edg[u].push_back(v);edg[v].push_back(u);
		to[u]++;to[v]++;tmp[u] = to[u];tmp[v] = to[v];
	}
	int ans = 0;
	for(int st = 1;st <= n;st++){
		for(int j = 1;j <= n;j++){to[j] = tmp[j];reach[j] = book[j] = 0;}
		int res = 0, cnt = 1;
		book[st] = 1;for(int i : edg[st])to[i]--,reach[i] = 1;
		while(cnt < n){
			res++;int pos0 = 0, to0 = -1, pos1 = 0, to1 = -1;
			for(int i = 1;i <= n;i++){
				if(!book[i] && reach[i]){
					if(to[i] > to0){
						pos1 = pos0;to1 = to0;
						pos0 = i;	to0 = to[i];
					}
					else if(to[i] > to1){
						pos1 = i;	to1 = to[i];
					}
				}
			}
			cnt++;book[pos0] = 1;
			for(int i : edg[pos0]){to[i]--;reach[i] = 1;}
			if(pos1){
				cnt++;book[pos1] = 1;
				for(int i : edg[pos1]){to[i]--;reach[i] = 1;}
			}
		}
		ans = max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
